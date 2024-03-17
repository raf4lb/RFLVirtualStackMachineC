import sys

INSTRUCTIONS = {
    'HLT': 0,
    'PSH': 1,
    'PSHL': 2,
    'POP': 3,
    'DLY': 4,
    'TOP': 5,
    'ADD': 6,
    'SUB': 7,
    'MUL': 8,
    'DIV': 9,
    'JMP': 10,
    'JE': 11,
    'JL': 12,
    'JG': 13,
    'JLE': 14,
    'JGE': 15,
    'CALL': 16,
    'RET': 17,
    'AND': 18,
    'OR': 19,
    'XOR': 20,
    'NOT': 21,
    'LSH': 22,
    'RSH': 23,
}


def strip(lines: list[str]) -> None:
  for i, line in enumerate(lines):
    lines[i] = line.strip()


def remove_comments(lines: list[str]) -> list[str]:
  for line, content in enumerate(lines):
    index = content.find(";")
    if index > -1:
      lines[line] = content[:index]
  return lines


def remove_blank_lines(lines: list[str]) -> list[str]:
  return [line for line in lines if line]


def remove_jumps(lines: list[str]):
  return [line for line in lines if not line.startswith(';')]


def build_jumps(lines: list[str]) -> list[str]:
  new_lines = []
  addresses = {}
  for line, content in enumerate(lines):
    if content.startswith('.'):
      addresses[content[1:]] = line - len(addresses)
    else:
      new_lines.append(content)

  new_lines = remove_jumps(new_lines)
  for line, content in enumerate(new_lines):
    if '.' in content:
      instruction, label = content.split(" ")
      new_lines[line] = f"{instruction} {addresses[label[1:]]}"
  return new_lines


def remove_vars(lines: list[str]) -> list[str]:
  return [line for line in lines if not line.startswith('VAR')]


def build_vars(lines: list[str], total_port_banks: int):
  addresses = {}
  for line in lines:
    if line.startswith('VAR'):
      var_name = line.split(" ")[1]
      addresses[var_name] = total_port_banks + len(addresses)

  new_lines = remove_vars(lines)
  for line, content in enumerate(new_lines):
    if '$' in content:
      instruction, var_name = content.split(" ")
      new_lines[line] = f"{instruction} {addresses[var_name[1:]]}"
  return new_lines


def pprint(lines):
  for line, content in enumerate(lines):
    print(f"{line}\t", content)


def compile_rfl(filename: str, total_port_banks=0, debug=False) -> list[int]:
  program = []
  with open(filename) as p:
    lines = p.read().splitlines()
    lines = remove_comments(lines)
    strip(lines)
    lines = remove_blank_lines(lines)
    lines = build_vars(lines, total_port_banks)
    lines = build_jumps(lines)
    if debug:
      dline = 0
    for line in lines:
      instruction = line.split(" ")
      if debug:
        print(f"{dline}\t", instruction)
        dline += 1
      opcode = bin(INSTRUCTIONS[instruction[0]])[2:]
      operand = bin(int(instruction[1]))[2:] if len(instruction) == 2 else '0'
      operand = operand.zfill(16)
      program.append(int(f"{opcode}{operand}", 2))
  return program


if __name__ == '__main__':
  total_port_banks = int(sys.argv[2])
  program = compile_rfl(sys.argv[1], total_port_banks)
  program_len = len(program)
  print(program, program_len)
