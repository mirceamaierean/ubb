use std::collections::HashMap;
use std::fs;

use crate::finite_automata::FiniteAutomata;
pub struct FileReader {}

impl FileReader {
    pub fn read_file(file_name: &str) -> Vec<String> {
        fs::read_to_string(file_name)
            .unwrap()
            .split('\n')
            .map(|s| s.trim().to_string())
            .filter(|s| !s.is_empty())
            .collect()
    }

    pub fn get_reserved_tokens(file_name: &str) -> Vec<String> {
        let mut reserved_tokens: Vec<String> = FileReader::read_file(file_name);
        reserved_tokens.push("\n".to_string());
        reserved_tokens.push(" ".to_string());

        reserved_tokens
    }

    fn parse_line(line: &str) -> Vec<String> {
        line.split(':').collect::<Vec<&str>>()[1]
            .replace(['{', '}'], "")
            .split(',')
            .map(|s| s.trim().to_string())
            .collect()
    }

    fn parse_final_state(line: &str) -> String {
        line.split(':').collect::<Vec<&str>>()[1].trim().to_string()
    }

    fn parse_transition(line: &str) -> (String, String, String) {
        let parts = line
            .split('=')
            .collect::<Vec<&str>>()
            .iter()
            .map(|s| s.trim())
            .collect::<Vec<&str>>();

        // parts[0] won't live enough after replace, make borrow checker happy
        let begin_and_symbols = parts[0].replace(['(', ')'], "");
        let begin_and_symbols = begin_and_symbols.split(' ').collect::<Vec<&str>>();

        (
            begin_and_symbols[0].to_string(),
            begin_and_symbols[1].to_string(),
            parts[1].to_string(),
        )
    }

    pub fn build_automata(file_name: &str) -> FiniteAutomata {
        let lines = FileReader::read_file(file_name);
        let mut states: Vec<String> = Vec::new();
        let mut alphabet: Vec<String> = Vec::new();
        let mut final_states: Vec<String> = Vec::new();
        let mut initial_state: String = String::new();
        let mut transitions_hashmap: HashMap<(String, String), String> = HashMap::new();

        for line in lines {
            // match the first character of the line
            match line.chars().next() {
                Some('Q') => {
                    states = FileReader::parse_line(&line);
                }
                Some('Σ') => {
                    alphabet = FileReader::parse_line(&line);
                    alphabet.push(' '.to_string());
                }
                Some('F') => {
                    final_states = FileReader::parse_line(&line);
                }
                Some('q') => {
                    initial_state = FileReader::parse_final_state(&line);
                }
                Some('δ') => {
                    let transitions = FileReader::parse_line(&line);

                    for transition in transitions {
                        let (start, symbols, end) = FileReader::parse_transition(&transition);
                        for symbol in symbols.chars() {
                            transitions_hashmap
                                .insert((start.clone(), symbol.to_string()), end.clone());
                        }
                    }
                }
                _ => {}
            }
        }

        FiniteAutomata::new(
            states,
            alphabet,
            initial_state,
            final_states,
            transitions_hashmap,
        )
    }
}
