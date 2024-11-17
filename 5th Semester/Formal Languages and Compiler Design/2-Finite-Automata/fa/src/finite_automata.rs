use std::collections::HashMap;

pub struct FiniteAutomata {
    states: Vec<String>,
    alphabet: Vec<String>,
    initial_state: String,
    final_states: Vec<String>,
    transitions: HashMap<(String, String), String>,
}

impl FiniteAutomata {
    pub fn new(
        states: Vec<String>,
        alphabet: Vec<String>,
        initial_state: String,
        final_states: Vec<String>,
        transitions: HashMap<(String, String), String>,
    ) -> Self {
        FiniteAutomata {
            states,
            alphabet,
            initial_state,
            final_states,
            transitions,
        }
    }

    pub fn get_states(&self) -> Vec<String> {
        self.states.clone()
    }

    pub fn get_alphabet(&self) -> Vec<String> {
        self.alphabet.clone()
    }

    pub fn get_initial_state(&self) -> String {
        self.initial_state.clone()
    }

    pub fn get_final_states(&self) -> Vec<String> {
        self.final_states.clone()
    }

    pub fn get_transitions(&self) -> HashMap<(String, String), String> {
        self.transitions.clone()
    }

    pub fn check_word(&self, word: &str) -> bool {
        let mut current_state = self.initial_state.clone();
        for c in word.chars() {
            match self
                .transitions
                .get(&(current_state.clone(), c.to_string()))
            {
                Some(next_state) => {
                    current_state.clone_from(next_state);
                }
                None => {
                    return false;
                }
            }
        }
        self.final_states.contains(&current_state)
    }
}
