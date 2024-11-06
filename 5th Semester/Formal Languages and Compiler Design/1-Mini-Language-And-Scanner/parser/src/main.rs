use regex::Regex;
use std::env;
mod symbol_table;
use std::fs;
use std::io::Write;

struct TokenProcessor {
    separators_regex: Regex,
    string_constant_regex: Regex,
    char_constant_regex: Regex,
    operators_regex_expression: Regex,
    int_constant_regex: Regex,
    float_constant_regex: Regex,
    identifier_regex: Regex,
    reserved_tokens: Vec<String>,
    symbol_table: symbol_table::SymbolTable,
}

impl TokenProcessor {
    fn new(reserved_tokens: Vec<String>) -> Self {
        TokenProcessor {
            symbol_table: symbol_table::SymbolTable::new(None),
            reserved_tokens,
            separators_regex: Regex::new(r"[(]|[)]|[{]|[}]|,|[ ]|;").unwrap(),
            operators_regex_expression: Regex::new(r"([+]|[-]|[*]|[%]|[/]|[*]|=|!|<|>|[&]|[|])+")
                .unwrap(),
            int_constant_regex: Regex::new(r"^(0|([+-]?[1-9][0-9]*))$").unwrap(),
            float_constant_regex: Regex::new(r"^(0|([+-]?[1-9][0-9]*)([.][0-9]*)?)$").unwrap(),
            identifier_regex: Regex::new(r"^[a-zA-Z_][a-zA-Z0-9_]*$").unwrap(),
            string_constant_regex: Regex::new(r#""([^"\\]|\\.)*""#).unwrap(),
            char_constant_regex: Regex::new(r#"'([^'"]|\\'|\\")'"#).unwrap(),
        }
    }

    fn process_program(&mut self, program: Vec<String>) -> Vec<String> {
        let processed_program = self.process(&program, self.string_constant_regex.clone());
        let processed_program = self.process(&processed_program, self.char_constant_regex.clone());
        let processed_program =
            self.process(&processed_program, self.operators_regex_expression.clone());
        let processed_program = self.process(&processed_program, self.separators_regex.clone());

        processed_program
            .into_iter()
            .map(|s| s.trim().to_string())
            .filter(|s| !s.is_empty())
            .collect()
    }

    fn process(&self, program: &Vec<String>, regex: Regex) -> Vec<String> {
        let mut processed_program = Vec::new();

        for token in program {
            if !((token.starts_with("\"") && token.ends_with("\""))
                || (token.starts_with("'") && token.ends_with("'")))
            {
                let mut last_index = 0;

                for cap in regex.find_iter(token) {
                    if cap.start() > last_index {
                        processed_program.push(token[last_index..cap.start()].to_string());
                    }
                    processed_program.push(token[cap.start()..cap.end()].to_string());
                    last_index = cap.end();
                }
                if last_index < token.len() {
                    processed_program.push(token[last_index..].to_string());
                }
            } else {
                processed_program.push(token.to_string());
            }
        }

        processed_program
    }

    fn check_reserved(&self, token: &String) -> bool {
        self.reserved_tokens.contains(token)
    }

    fn get_symbol_table_value(&mut self, key: String) -> usize {
        match self.symbol_table.get(key.clone()) {
            Some(value) => value,
            None => {
                self.symbol_table.insert(key.clone());
                self.symbol_table.get(key).unwrap()
            }
        }
    }

    fn print_symbol_table_to_file(&self, file: &mut fs::File) {
        for value in self.symbol_table.get_sorted_hash_table().iter().flatten() {
            file.write_all(format!("{} : {}\n", value.1, value.0).as_bytes())
                .unwrap();
        }
    }

    fn write_to_file(&mut self, program: Vec<String>, file: &mut fs::File) -> Option<String> {
        let mut pif_answer = String::new();

        for line in program {
            let mut valid_token = true;
            let result = match line.as_str() {
                _ if self.check_reserved(&line) => format!("{} : {}\n", line, -1),
                _ if self.int_constant_regex.is_match(&line)
                    || self.float_constant_regex.is_match(&line)
                    || self.string_constant_regex.is_match(&line)
                    || self.char_constant_regex.is_match(&line)
                    || self.identifier_regex.is_match(&line) =>
                {
                    let index = self.get_symbol_table_value(line.clone());
                    format!("{} : {}\n", line, index)
                }

                _ => {
                    valid_token = false;
                    format!("Lexical error caused by invalid token: {}\n", line)
                }
            };

            if !valid_token {
                return Some(line);
            }

            pif_answer.push_str(&result);
        }

        file.write_all(pif_answer.as_bytes()).unwrap();

        None
    }
}

fn main() {
    let mut args = env::args();

    if args.len() != 3 {
        println!("Usage: cargo run tokens.in <program.mm>");
        return;
    }

    args.next();

    let mut reserved_tokens: Vec<String> = fs::read_to_string(args.next().unwrap())
        .unwrap()
        .split("\n")
        .map(|s| s.trim().to_string())
        .filter(|s| !s.is_empty())
        .collect();

    reserved_tokens.push("\n".to_string());
    reserved_tokens.push(" ".to_string());

    let program = fs::read_to_string(args.next().unwrap())
        .unwrap()
        .split("\n")
        .map(|s| s.trim().to_string())
        .filter(|s| !s.is_empty())
        .collect::<Vec<String>>();

    let original_program = program.clone();

    let mut processor = TokenProcessor::new(reserved_tokens);
    let processed_program = processor.process_program(program);

    let mut pif_file = fs::File::create("pif.out").unwrap();
    let mut st_file = fs::File::create("st.out").unwrap();

    match processor.write_to_file(processed_program, &mut pif_file) {
        Some(invalid) => {
            let line_number = original_program
                .iter()
                .position(|s| s.contains(&invalid))
                .unwrap();
            pif_file
                .write_all(
                    format!(
                        "Lexical error at line {} caused by {} \n",
                        line_number + 1,
                        invalid
                    )
                    .as_bytes(),
                )
                .unwrap();
        }
        None => {
            println!("Lexical analysis was successful");
        }
    }

    processor.print_symbol_table_to_file(&mut st_file);
}
