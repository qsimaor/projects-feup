#!/usr/bin/env python3

import ast

def log_and_execute(node):
    print(f"Executing line {node.lineno}: {node.col_offset} | {ast.get_source_segment(source, node)}")
    exec(compile(ast.Module([node]), '<string>', 'exec'), globals())

# Arquivo Python a ser executado
file_to_execute = './get-publications-new.py flup'

# Ler o código do arquivo
with open(file_to_execute, 'r') as file:
    source = file.read()

# Analisar o código-fonte para obter a árvore de sintaxe abstrata (AST)
tree = ast.parse(source, filename='<string>', mode='exec')

# Percorrer o AST e executar cada nó
for node in ast.walk(tree):
    if isinstance(node, ast.stmt):
        log_and_execute(node)

