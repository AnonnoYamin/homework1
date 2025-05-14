#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOTES 3

const char VALID_NOTES[] = "ABCDEFG";

typedef struct {
    char note;
    int octave;
} Note;

typedef struct {
    Note notes[MAX_NOTES];
} Chord;

int getNoteIndex(char note) {
    for (int i = 0; i < 7; ++i) {
        if (VALID_NOTES[i] == note) return i;
    }
    return -1;
}

int isValidNoteChar(char note) {
    return strchr(VALID_NOTES, note) != NULL;
}

int isDuplicateNotes(Note *notes) {
    for (int i = 0; i < MAX_NOTES; ++i) {
        for (int j = i + 1; j < MAX_NOTES; ++j) {
            if (notes[i].note == notes[j].note && notes[i].octave == notes[j].octave)
                return 1;
        }
    }
    return 0;
}

int isSameOctave(Note *notes) {
    int refOctave = notes[0].octave;
    for (int i = 1; i < MAX_NOTES; ++i) {
        if (notes[i].octave != refOctave)
            return 0;
    }
    return 1;
}

int calculateInterval(char lowNote, char highNote) {
    int lowIndex = getNoteIndex(lowNote);
    int highIndex = getNoteIndex(highNote);
    if (lowIndex == -1 || highIndex == -1) return -1;
    return highIndex - lowIndex;
}

void checkHarmony(Note *notes) {
    int i1 = calculateInterval(notes[0].note, notes[1].note);
    int i2 = calculateInterval(notes[0].note, notes[2].note);

    if (i1 < 0 || i2 < 0) {
        printf("Invalid pitch interval for harmony evaluation.\n");
        return;
    }

    if ((i1 == 2 || i1 == 3) && (i2 == 4 || i2 == 5)) {
        printf("Harmony status: Harmonious\n");
    } else {
        printf("Harmony status: Not Harmonious\n");
    }
}

void learnMusicTheory() {
    Chord chord;
    printf("\n--- Music Theory Learning ---\n");
    for (int i = 0; i < MAX_NOTES; ++i) {
        char noteChar;
        int octave;
        printf("Enter note %d (A-G): ", i + 1);
        scanf(" %c", &noteChar);
        noteChar = toupper(noteChar);

        if (!isValidNoteChar(noteChar)) {
            printf("Invalid note. Use A-G only.\n");
            return;
        }

        printf("Enter octave for note %d (1-8): ", i + 1);
        scanf("%d", &octave);

        if (octave < 1 || octave > 8) {
            printf("Invalid octave. Use 1-8 only.\n");
            return;
        }

        chord.notes[i].note = noteChar;
        chord.notes[i].octave = octave;
    }

    printf("\nChord Information:\n");
    for (int i = 0; i < MAX_NOTES; ++i) {
        printf("Note %d: %c%d\n", i + 1, chord.notes[i].note, chord.notes[i].octave);
    }

    if (!isSameOctave(chord.notes)) {
        printf("Chord invalid: Notes are not in the same octave.\n");
        return;
    }

    if (isDuplicateNotes(chord.notes)) {
        printf("Chord invalid: Duplicate notes detected.\n");
        return;
    }

    printf("Chord valid.\n");
    checkHarmony(chord.notes);
}

int main() {
    learnMusicTheory();
    return 0;
}
