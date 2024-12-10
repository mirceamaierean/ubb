use crate::finite_automata;
use crate::symbol_table;
use regex::Regex;
use std::fs;
use std::io::Write;

pub struct TokenProcessor {
    separators_regex: Regex,
    string_constant_regex: Regex,
    char_constant_regex: Regex,
    operators_regex_expression: Regex,
    // int_constant_regex: Regex,
    // float_constant_regex: Regex,
    // identifier_regex: Regex,
    reserved_tokens: Vec<String>,
    symbol_table: symbol_table::SymbolTable,
}

impl TokenProcessor {
    pub fn new(reserved_tokens: Vec<String>) -> Self {
        TokenProcessor {
            symbol_table: symbol_table::SymbolTable::new(None),
            reserved_tokens,
            separators_regex: Regex::new(r"[(]|[)]|[{]|[}]|,|[ ]|;").unwrap(),
            operators_regex_expression: Regex::new(r"([+]|[-]|[*]|[%]|[/]|[*]|=|!|<|>|[&]|[|])+")
                .unwrap(),
            // int_constant_regex: Regex::new(r"^(0|([+-]?[1-9][0-9]*))$").unwrap(),
            // float_constant_regex: Regex::new(r"^(0|([+-]?[1-9][0-9]*)([.][0-9]*)?)$").unwrap(),
            // identifier_regex: Regex::new(r"^[a-zA-Z_][a-zA-Z0-9_]*$").unwrap(),
            string_constant_regex: Regex::new(r#""([^"\\]|\\.)*""#).unwrap(),
            char_constant_regex: Regex::new(r#"'([^'"]|\\'|\\")'"#).unwrap(),
        }
    }

    pub fn process_program(&mut self, program: Vec<String>) -> Vec<String> {
        let processed_program = TokenProcessor::process(&program, &self.string_constant_regex);
        let processed_program =
            TokenProcessor::process(&processed_program, &self.char_constant_regex);
        let processed_program =
            TokenProcessor::process(&processed_program, &self.operators_regex_expression);
        let processed_program = TokenProcessor::process(&processed_program, &self.separators_regex);

        processed_program
            .into_iter()
            .map(|s| s.trim().to_string())
            .filter(|s| !s.is_empty())
            .collect()
    }

    fn process(program: &Vec<String>, regex: &Regex) -> Vec<String> {
        let mut processed_program = Vec::new();

        for token in program {
            if (token.starts_with('\"') && token.ends_with('\"'))
                || (token.starts_with('\'') && token.ends_with('\''))
            {
                processed_program.push(token.to_string());
            } else {
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
            }
        }

        processed_program
    }

    fn check_reserved(&self, token: &String) -> bool {
        self.reserved_tokens.contains(token)
    }

    fn get_symbol_table_value(&mut self, key: &str) -> usize {
        if let Some(value) = self.symbol_table.get(key) {
            return value;
        }

        self.symbol_table.insert(key.to_string());
        self.symbol_table.get(key).unwrap()
    }

    pub fn print_symbol_table_to_file(&self, file: &mut fs::File) {
        for value in self.symbol_table.get_sorted_hash_table().iter().flatten() {
            file.write_all(format!("{} : {}\n", value.1, value.0).as_bytes())
                .unwrap();
        }
    }

    pub fn write_to_file(
        &mut self,
        program: Vec<String>,
        file: &mut fs::File,
        finite_automata: &finite_automata::FiniteAutomata,
    ) -> Option<String> {
        let mut pif_answer = String::new();

        for line in program {
            let mut valid_token = true;
            let result = match line.as_str() {
                _ if self.check_reserved(&line) => format!("{} : {}\n", line, -1),
                _ if finite_automata.check_word(&line)
                    // || self.float_constant_regex.is_match(&line)
                    // || self.string_constant_regex.is_match(&line)
                    // || self.char_constant_regex.is_match(&line) 
                    =>
                {
                    let index = self.get_symbol_table_value(line.as_str());
                    format!("id: {index}\n")
                }

                _ => {
                    valid_token = false;
                    format!("Lexical error caused by invalid token: {line}\n",)
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
