mod file_reader;
mod finite_automata;
mod symbol_table;
mod token_processor;
use crate::token_processor::TokenProcessor;
use std::env;
use std::fs;
use std::io::Write;

fn main() {
    let mut args = env::args();

    if args.len() != 4 {
        println!("Usage: cargo run <program.mm> tokens.in fa.in");
        return;
    }

    args.next();

    let program = file_reader::FileReader::read_file(&args.next().unwrap());
    let reserved_tokens = file_reader::FileReader::get_reserved_tokens(&args.next().unwrap());
    let finite_automata = file_reader::FileReader::build_automata(&args.next().unwrap());

    let mut processor = TokenProcessor::new(reserved_tokens);

    let original_program = program.clone();
    let processed_program = processor.process_program(program);

    let mut pif_file = fs::File::create("pif.out").unwrap();
    let mut st_file = fs::File::create("st.out").unwrap();

    match processor.write_to_file(processed_program, &mut pif_file, &finite_automata) {
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

    // menu driven console for finite_automata
    print!("1) States\n2) Alphabet\n3) Initial State\n4) Final States\n5) Transitions\n");
    let mut choice = String::new();
    std::io::stdin().read_line(&mut choice).unwrap();
    let choice: usize = choice.trim().parse().unwrap();
    match choice {
        1 => {
            println!("States: {:?}", finite_automata.get_states());
        }
        2 => {
            println!("Alphabet: {:?}", finite_automata.get_alphabet());
        }
        3 => {
            println!("Initial State: {:?}", finite_automata.get_initial_state());
        }
        4 => {
            println!("Final States: {:?}", finite_automata.get_final_states());
        }
        5 => {
            println!("Transitions: {:?}", finite_automata.get_transitions());
        }
        _ => {
            println!("Invalid choice");
        }
    }
}
