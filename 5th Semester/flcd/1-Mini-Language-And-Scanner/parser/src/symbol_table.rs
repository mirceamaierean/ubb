pub struct SymbolTable {
    // The hash table is a vector of Option<(String, u64)>, where the string is the key
    // and the u64 represents the value associated with the string in the symbol table
    hash: Vec<Option<(String, usize)>>,
    // The position is the number of elements that have been inserted in the hash table
    // Conversely, it corresponds to the index in the symbol table of the next element to be inserted
    position: usize,
}

impl SymbolTable {
    pub fn new(capactity: Option<usize>) -> SymbolTable {
        let cap = capactity.unwrap_or(16);
        Self {
            hash: vec![None; cap],
            position: 0,
        }
    }

    // takes a string and returns a hash value
    fn first_hash(&self, key: &str) -> usize {
        key.chars()
            .map(|c| c as usize)
            .reduce(|acc, el| {
                (((acc as u64) * 41 + (el as u64)) % (self.hash.len() as u64)) as usize
            })
            .unwrap()
    }

    fn second_hash(&self, key: &str) -> usize {
        (2 * key
            .chars()
            .map(|c| c as usize)
            .reduce(|acc, el| {
                (((acc as u64) * 61 + (el as u64)) % (self.hash.len() as u64)) as usize
            })
            .unwrap()
            + 1)
            % self.hash.len()
    }

    // pos is the number of times we have tried to insert the key
    fn hash_function(&self, key: &str, pos: usize) -> usize {
        (((self.first_hash(key) as u64) + (pos as u64) * (self.second_hash(key) as u64))
            % (self.hash.len() as u64)) as usize
    }

    fn put(&mut self, item: (String, usize)) {
        if self.hash.len() == self.position {
            self.rehash();
        }

        let mut pos = 0;

        loop {
            let hash_pos = self.hash_function(&item.0, pos);
            if Option::is_none(&self.hash[hash_pos]) {
                self.hash[hash_pos] = Some(item);
                self.position += 1;
                break;
            }

            if Option::is_some(&self.hash[hash_pos]) {
                let current_item = self.hash[hash_pos].clone().unwrap();
                if current_item.0 == item.0 {
                    break;
                }
            }

            pos += 1;
        }
    }

    fn rehash(&mut self) {
        let mut new_hash = SymbolTable::new(Some(self.hash.len() * 2));
        self.hash
            .iter()
            .for_each(|x| new_hash.put(x.clone().unwrap()));
        self.hash = new_hash.hash;
    }

    pub fn insert(&mut self, key: String) {
        self.put((key, self.position));
    }

    pub fn get_sorted_hash_table(&self) -> Vec<Option<(String, usize)>> {
        // sort this based on usize
        let mut hash = self.hash.clone();
        hash.sort_by(|a, b| {
            if a.is_none() {
                return std::cmp::Ordering::Greater;
            }
            if b.is_none() {
                return std::cmp::Ordering::Less;
            }
            let a = a.clone().unwrap();
            let b = b.clone().unwrap();
            a.1.cmp(&b.1)
        });

        hash
    }

    pub fn get(&self, key: String) -> Option<usize> {
        let mut pos = 0;

        loop {
            let hash_pos = self.hash_function(&key, pos);

            if Option::is_none(&self.hash[hash_pos]) {
                return None;
            }
            if let Some(current_item) = &self.hash[hash_pos] {
                if current_item.0 == key {
                    return Some(current_item.1);
                }
            }

            pos += 1;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_insert_size() {
        let mut st = SymbolTable::new(Some(2));

        st.insert("hello".to_string());
        st.insert("world".to_string());
        st.insert("this".to_string());
        st.insert("is".to_string());
        st.insert("test".to_string());
        st.insert("a".to_string());
        st.insert("a".to_string());
        st.insert("a".to_string());
        st.insert("a".to_string());

        assert_eq!(st.position, 6);
    }

    #[test]
    fn test_insert_existing_variable() {
        let mut st = SymbolTable::new(Some(2));

        st.insert("hello".to_string());
        st.insert("world".to_string());
        st.insert("this".to_string());
        st.insert("is".to_string());
        st.insert("test".to_string());

        // assert that hello is part of the symbol table
        assert_eq!(st.get("hello".to_string()), Some(0));
        // assert that world is part of the symbol table
        assert_eq!(st.get("world".to_string()), Some(1));
        assert_eq!(st.get("this".to_string()), Some(2));
        assert_eq!(st.get("is".to_string()), Some(3));
        assert_eq!(st.get("test".to_string()), Some(4));
    }

    #[test]
    fn test_get_empty_table() {
        let st = SymbolTable::new(Some(2));

        assert_eq!(st.get("hello".to_string()), None);
    }

    #[test]
    fn test_get_hash_has_values() {
        let mut st = SymbolTable::new(Some(2));

        st.insert("hello".to_string());
        st.insert("world".to_string());
        st.insert("this".to_string());
        st.insert("is".to_string());
        st.insert("test".to_string());

        assert_eq!(st.get("not".to_string()), None);
    }
}
