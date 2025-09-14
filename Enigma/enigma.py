import json
import sys

class Enigma:
    def __init__(self, hash_map, wheels, reflector_map):
        self.hash_map = hash_map
        self.wheels = wheels
        self.reflector_map = reflector_map
        self.encrypted_characters = 0

    def get_key_by_value(self, d, value):
        for key, val in d.items():
            if val == value:
                return key
        return None


    def encrypt_character(self, character):
        i = self.hash_map[character]
        value = (((2 * self.wheels[0]) - self.wheels[1] + self.wheels[2]) % 26)
        if value != 0:
            i += value
        else:
            i += 1
        i = i % 26
        c1 = self.get_key_by_value(self.hash_map, i)
        c2 = self.reflector_map[c1]
        i = self.hash_map[c2]
        if value != 0:
            i -= value
        else:
            i -= 1
        i = i % 26
        c3 = self.get_key_by_value(self.hash_map, i)
        return c3

    def advance_wheels(self):
        self.wheels[0] = (self.wheels[0] % 8) + 1

        if self.encrypted_characters % 2 == 0:
            self.wheels[1] *= 2
        else:
            self.wheels[1] -= 1

        if self.encrypted_characters % 10 == 0:
            self.wheels[2] = 10
        elif self.encrypted_characters % 3 == 0:
            self.wheels[2] = 5
        else:
            self.wheels[2] = 0


    def encrypt(self, message):
        initial_wheels = self.wheels.copy()
        encrypted = ""
        for ch in message:
            if ch.islower():
                encrypted += self.encrypt_character(ch)
                self.encrypted_characters += 1
            else:
                encrypted += ch
            self.advance_wheels()
        self.wheels = initial_wheels
        self.encrypted_characters = 0
        return encrypted


class JSONFileError(Exception):
    pass


def load_enigma_from_path(path):
    try:
        with open(path, "r") as path_file:
            data = json.load(path_file)
            hash_map = data["hash_map"]
            reflector_map = data["reflector_map"]
            wheels = data["wheels"]
            return Enigma(hash_map, wheels, reflector_map)
    except Exception:
        raise JSONFileError



def parser():
    ERROR_USAGE = "Usage: python3 enigma.py -c <config_file> -i <input_file> -o <output_file>"
    flags = {'-c', '-i', '-o'}
    paths = {'-c': None, '-i': None, '-o': None}

    if len(sys.argv) not in [5, 7]:
        print(ERROR_USAGE, file=sys.stderr)
        exit(1)

    for i in range(1, len(sys.argv), 2):
        if sys.argv[i] not in flags:
            print(ERROR_USAGE, file=sys.stderr)
            exit(1)
        paths[sys.argv[i]] = sys.argv[i + 1]

    if not paths['-c'] or not paths['-i']:
        print(ERROR_USAGE, file=sys.stderr)
        exit(1)

    return paths['-c'], paths['-i'], paths['-o']



def main():
    ERROR_SCRIPT = "The enigma script has encountered an error"

    config_path, input_path, output_path = parser()

    try:
        enigma = load_enigma_from_path(config_path)
        with open(input_path, 'r') as infile:
            output_file = open(output_path, 'w') if output_path else sys.stdout
            for line in infile:
                encrypted_message = enigma.encrypt(line)
                print(encrypted_message, file=output_file, end='')
            if output_path:
                output_file.close()
    except Exception:
        print(ERROR_SCRIPT, file=sys.stderr)
        exit(1)

if __name__ == "__main__":
    main()
