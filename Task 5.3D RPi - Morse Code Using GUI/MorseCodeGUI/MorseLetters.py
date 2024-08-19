def get_morse_sequence(letter):
    morse_letter_sequences = {
        'A': "*-",
        'B': "-***",
        'C': "-*-*",
        'D': "-**",
        'E': "*",
        'F': "**-*",
        'G': "--*",
        'H': "****",
        'I': "**",
        'J': "*---",
        'K': "-*-",
        'L': "*-**",
        'M': "--",
        'N': "-*",
        'O': "---",
        'P': "*--*",
        'Q': "--*-",
        'R': "*-*",
        'S': "***",
        'T': "-",
        'U': "**-",
        'V': "***-",
        'W': "*--",
        'X': "-**-",
        'Y': "-*--",
        'Z': "--**"
    }
    letter = letter.upper()


    return morse_letter_sequences.get(letter)