from Grammar import Grammar
from Tree import Tree
class Parser:
    @staticmethod
    def read_from_file(filename):
        P = {}
        with open(filename, "r") as grammar_file:
            N = Parser.parse_line(grammar_file.readline())
            sigma = Parser.parse_line(grammar_file.readline())
            sigma.append('')
            S = Parser.parse_line(grammar_file.readline())[0]
            grammar_file.readline()
            for line in grammar_file:
                Parser.parse_non_terminals(P, line)
        return Grammar(N, sigma, P, S)

    @staticmethod
    def parse_line(line):
        line = line.strip().split("=>")[1]
        line = line.strip()
        symbols = line.split(" ")
        symbols = list(filter(None, symbols))
        return symbols

    @staticmethod
    def parse_non_terminals(P, line):
        line = line.strip().split("->")
        key = line[0].strip()
        line = line[1].strip()
        line = line.split("|")
        line = [prod.strip() for prod in line]
        # if there is an epsilon production, mark it as ""
        for i in range(len(line)):
            if line[i] == "epsilon":
                line[i] = ""
        P[key] = line

    @staticmethod
    def parse_tokens(G, filename):
        with(open(filename, "r")) as file:
            tokens = [eval(line.strip())[0] for line in file] 
        tokens.append('$')
        return tokens