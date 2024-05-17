/**
 * @file main.c
 * @author Corentin L.
 * @version 1.0
 * @brief EN : University Training Management / FR : Gestion D'Une Formation Universitaire
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#pragma warning(disable:4996)

// Definition of new types
/**
 * @enum Bool
 * @brief Boolean values
 */
typedef enum {
    TRUE = 1,
    FALSE = 0
} Bool;

/**
 * @brief Maximum dimensions
 */
enum {
    NB_SEMESTRES = 2,
    MIN_UE = 3,
    MAX_UE = 6,
    MAX_MATIERES = 10,
    MAX_EPREUVES = 5,
    MAX_ETUDIANTS = 100,
    MAX_CHAR = 30
};

// Limits : ratings 
const float MIN_NOTE = 0.f, MAX_NOTE = 20.f;

// Definition of new types : structures
/**
 * @struct Epreuve
 */
typedef struct {
    char nomEpreuve[MAX_CHAR];
    float coef[MAX_UE];
} Epreuve;

/**
 * @struct Matiere
 */
typedef struct {
    char nomMatiere[MAX_CHAR];
    int nbEpreuves;
    Epreuve epreuves[MAX_EPREUVES];
} Matiere;

/**
 * @struct Semestre
 */
typedef struct {
    int nbMatieres;
    Matiere matieres[MAX_MATIERES];
} Semestre;

/**
 * @struct Etudiant
 */
typedef struct {
    char nom[MAX_CHAR];
    // Maximum number of notes for a student
    float notes[MAX_EPREUVES * MAX_MATIERES * NB_SEMESTRES];
} Etudiant;

/**
 * @struct Formation
 */
typedef struct {
    int nbUE;
    int nbETU;
    Etudiant etudiant[MAX_ETUDIANTS];
    Semestre semestres[NB_SEMESTRES];
} Formation;

// UTILITY FUNCTIONS

/**
 * @brief Initialization of training elements
 * @param f Training to initialize
 */
void init_form(Formation *f) {
    f->nbUE = 0;
    f->nbETU = 0;
    for (unsigned int sem = 0; sem < NB_SEMESTRES; ++sem) {
        f->semestres[sem].nbMatieres = 0;
        for (unsigned int sub = 0; sub < MAX_MATIERES; ++sub) {
            f->semestres[sem].matieres[sub].nbEpreuves = 0;
        }
    }
}

/**
 * @brief Calculation of the sum of the coefficients for each teaching unit of a semester
 * @param f Training studied
 * @param semester_number Semester number studied
 * @return 1 if the coefficients are incorrect, 0 otherwise
 */
Bool incorrect_coefficients(const Formation *f, unsigned int semester_number) {
    const Semestre* s = &(f->semestres[semester_number]);
    float coef, sum_coef;
    for (unsigned int ue = 0; ue < f->nbUE; ++ue) {
        sum_coef = 0;
        for (unsigned int sub = 0; sub < s->nbMatieres; ++sub) {
            const Matiere* m = &(s->matieres[sub]);
            for (unsigned int epr = 0; epr < m->nbEpreuves; ++epr) {
                const Epreuve* e = &(m->epreuves[epr]);
                coef = e->coef[ue];
                if (coef < 0) {
                    return 1;
                }
                sum_coef += coef;
            }
        }
        if (sum_coef == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Checks if a subject exists
 * @param f Training studied
 * @param semester_number Semester number studied
 * @param test_exist_subject Subject existence test
 * @return subject index if subject exists, -1 otherwise
 * @return -1 if subject does not exist
 */
int subject_exist_verification(const Formation *f, unsigned int semester_number, unsigned char test_exist_subject[]) {
    const Semestre *s = &(f->semestres[semester_number]);
    for (int sub = 0; sub < s->nbMatieres; ++sub) {
        const Matiere *m = &(s->matieres[sub]);
        if (strcmp(m->nomMatiere, test_exist_subject) == 0) {
            return sub;
        }
    }
    return -1;
}

/**
 * @brief Checks if a test exists based on the settings
 * @param f Training studied
 * @param semester_number Semester number studied
 * @param test_exist_subject Subject tested
 * @param test_existence_test Test existence test
 * @return subject index if subject exists, -1 otherwise
 */
int test_exist_verification(const Formation *f, unsigned int semester_number, unsigned char test_exist_subject[], unsigned char test_existence_test[]){
    const Semestre *s = &(f->semestres[semester_number]);
    for (int sub = 0; sub < s->nbMatieres; ++sub) {
        const Matiere *m = &(s->matieres[sub]);
        if (strcmp(m->nomMatiere, test_exist_subject) == 0) {
            for (int epr = 0; epr < m->nbEpreuves; ++epr) {
                const Epreuve *e = &(m->epreuves[epr]);
                if (strcmp(e->nomEpreuve, test_existence_test) == 0) {
                    return epr;
                }
            }
        }
    }
    return -1;
}

/**
 * @brief Checks if adding coefficients is impossible
 * @param f Training studied
 * @param coef Table of coefficients to add
 * @return 1 if adding is impossible, 0 otherwise
 */
Bool impossible_coefficients_addition(const Formation *f, const float coef[]) {
    float sum_coef = 0;
    for (unsigned int i = 0; i < f->nbUE; ++i) {
        if (coef[i] < 0) {
            return 1;
        }
        sum_coef += coef[i];
    }
    if (sum_coef == 0)
        return 1;
    return 0;
}

/**
 * @brief Student initialization
 * @param f Training studied
 * @param student_name Initialized student name
 */
void init_student(Formation *f, unsigned char student_name[]) {
    unsigned int id_student = f->nbETU;
    strcpy(f->etudiant[id_student].nom, student_name);
    for (int i = 0; i < (MAX_EPREUVES * MAX_MATIERES * NB_SEMESTRES); ++i) {
        f->etudiant[id_student].notes[i] = -1;
    }
}

/**
 * @brief Checks if the student exists in the structure
 * @param f Training studied
 * @param coef Student name to add
 * @return Student index if exists, -1 otherwise
 */
int student_exist_verification(const Formation *f, unsigned char student_name[]) {
    for (int i = 0; i < MAX_ETUDIANTS; ++i) {
        if (strcmp(f->etudiant[i].nom, student_name) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Checks if the note exists in the training
 * @param f Training studied
 * @param id_student Id of the studied student
 * @param id_note Id of the studied note
 * @return True if the note exists, False otherwise
 */
Bool note_exist_verification(const Formation *f, int id_student, unsigned int id_note) {
    if (f->etudiant[id_student].notes[id_note] == -1) {
        return 0;
    }
    return 1;
}

/**
 * @brief Calculates the note id
 * @param id_sem Semester id
 * @param id_sub Subject id
 * @param id_test Test id
 * @return Id of a note according to parameters
 */
unsigned int note_id(unsigned int id_sem, int id_sub, int id_test) {
    unsigned int id = 0;
    // 50 tests per semester max
    id += (MAX_EPREUVES * MAX_MATIERES) * id_sem;
    // 10 tests per subject
    id += (MAX_EPREUVES) * id_sub;
    // 1 note per test
    id += id_test;
    return id;
}

/**
 * @brief Checks if the given student has notes for all defined tests in the given semester
 * @param f Training studied
 * @param id_student Id of the studied student
 * @param semester_number Semester number studied
 * @return 1 if everything is good, 0 otherwise
 */
int notes_id_student_exist_verification(const Formation *f, int id_student, unsigned int semester_number) {
    const Semestre* sem = &(f->semestres[semester_number]);
    int nbMatiere = sem->nbMatieres;
    for (int id_sub = 0; id_sub < nbMatiere; ++id_sub) {
        int nbEpreuve = sem->matieres[id_sub].nbEpreuves;
        for (int id_test = 0; id_test < nbEpreuve; ++id_test) {
            unsigned int id_note = note_id(semester_number, id_sub, id_test);
            if (note_exist_verification(f, id_student, id_note) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

/**
 * @brief Calculates the length of the longest subject name
 * @param f Training studied
 * @param semester_number Semester number studied
 * @return maximum length in the semester
 */
int max_length_subject(const Formation* f, unsigned int semester_number) {
    const Semestre* sem = &(f->semestres[semester_number]);
    int max_length = strlen("Moyennes");
    for (int sub = 0; sub < sem->nbMatieres; ++sub) {
        int sub_length = strlen(sem->matieres[sub].nomMatiere);
        if (sub_length > max_length) {
            max_length = sub_length;
        }
    }
    return max_length;
}

/**
 * @brief Displays the number of UEs
 * @param nbUE Number of teaching units
 */
void nbUE_display(int nbUE) {
    for (int ue = 0; ue < nbUE; ++ue) {
        printf("%3s%-2d","UE",ue+1);
    }
    printf("\n");
}

/**
 * @brief Calculates a student's averages for a semester
 * @param f Training studied
 * @param semester_number Semester number studied
 * @param id_student Id of the studied student
 * @brief Displays the averages for each subject at each UE, and the average of the UE
 */
void UE_averages_calculation(const Formation *f, unsigned int semester_number, int id_student) {
    const Semestre *sem = &(f->semestres[semester_number]);
    // Sum of subject notes
    float sum_sub;
    // Sum of coefficients by subject
    float sum_coef_sub;
    // Sum of notes for an UE
    float sum_UE_notes[f->nbUE];
    // Sum of coefficients for UEs
    float sum_coef_UE[f->nbUE];
    for (int i = 0; i < f->nbUE; ++i) {
        sum_UE_notes[i] = 0;
        sum_coef_UE[i] = 0;
    }
    int max_length = max_length_subject(f, semester_number);
    printf("%*s",max_length+1,"");
    nbUE_display(f->nbUE);
    // Calculation of averages
    for (int sub = 0; sub < sem->nbMatieres; ++sub) {
        const Matiere *m = &(sem->matieres[sub]);
        int sub_length = strlen(m->nomMatiere);
        printf("%s%*s", m->nomMatiere,max_length-sub_length+1,"");
        for (int ue = 0; ue < f->nbUE; ++ue) {
            sum_sub = 0;
            sum_coef_sub = 0;
            for (int epr = 0; epr < m->nbEpreuves; ++epr) {
                const Epreuve *e = &(m->epreuves[epr]);
                unsigned int id_note = note_id(semester_number, sub, epr);
                float coeffSel = e->coef[ue];
                float noteSel = f->etudiant[id_student].notes[id_note] * coeffSel;
                sum_sub += noteSel;
                sum_coef_sub += coeffSel;
            }
            // Display of averages by subject
            if (sum_coef_sub == 0) {
                printf("%5s","ND ");
            }
            else {
                float moy = floorf(sum_sub / sum_coef_sub * 10.f) / 10.f;
                printf("%4.1f ", moy);
                sum_UE_notes[ue] += sum_sub;
                sum_coef_UE[ue] += sum_coef_sub;
            }
        }
        printf("\n");
    }
    // Display of averages by UE
    printf("--\nMoyennes");
    printf("%*s",max_length-strlen("Moyennes")+1,"");
    for (int ue = 0; ue < f->nbUE; ++ue) {
        float moy = floorf(sum_UE_notes[ue] / sum_coef_UE[ue] * 10.f) / 10.f;
        printf("%4.1f ",moy);
    }
    printf("\n");
}

/**
 * @brief Calculate the display of UE averages for each semester of the given student for the year
 * @param f Training studied
 * @param id_student Id of the studied student
 * @param averages_table Table of averages for the year
 */
void year_averages_calculation(const Formation *f, int id_student, float averages_table[]) {
    int max_length = strlen("Moyennes annuelles");
    printf("%*s",max_length+1,"");
    nbUE_display(f->nbUE);
    float sum_UE_notes;
    float sum_coef_UE;
    float UE_averages_calculation[NB_SEMESTRES][f->nbUE];
    // Calculation of averages for teaching units and semesters
    for (int sem = 0; sem < NB_SEMESTRES; ++sem) {
        printf("S%d%*s", sem + 1,max_length-1,"");
        const Semestre *s = &(f->semestres[sem]);
        for (int ue = 0; ue < f->nbUE; ++ue) {
            sum_UE_notes = 0;
            sum_coef_UE = 0;
            for (int sub = 0; sub < s->nbMatieres; ++sub) {
                const Matiere *m = &(s->matieres[sub]);
                for (int epr = 0; epr < m->nbEpreuves; ++epr) {
                    const Epreuve *e = &(m->epreuves[epr]);
                    unsigned int id_note = note_id(sem, sub, epr);
                    float coeffSel = e->coef[ue];
                    float noteSel = f->etudiant[id_student].notes[id_note] * coeffSel;
                    sum_UE_notes += noteSel;
                    sum_coef_UE += coeffSel;
                }
            }
            float moyUe = floorf(sum_UE_notes / sum_coef_UE * 10.f) / 10.f;
            UE_averages_calculation[sem][ue] = sum_UE_notes / sum_coef_UE;
            printf("%4.1f ", moyUe);
        }
        printf("\n");
    }
    for (int ue = 0; ue < f->nbUE; ++ue) {
        averages_table[ue]= floorf((UE_averages_calculation[0][ue] + UE_averages_calculation[1][ue]) / 2 * 10.f) / 10.f;
    }
}

/**
 * @brief Display of the annual averages and the decision of the jury
 * @param averages_table Table of averages for the year
 * @param nbUE Number of teaching units
 */
void final_decision_display(float averages_table[], int nbUE) {
    char acquisition[MAX_CHAR] = "";
    int max_length = strlen("Moyennes annuelles");
    printf("--\nMoyennes annuelles ");
    float ue_ac = 0;
    Bool ue_acquired = FALSE;
    for (int ue = 0; ue < nbUE; ++ue) {
        if (averages_table[ue] >= 10.0) {
            if (ue_acquired == FALSE) {
                ue_acquired = TRUE;
            }
            else {
                sprintf(acquisition+strlen(acquisition), ", ");
            }
            ue_ac += 1;
            sprintf(acquisition+strlen(acquisition), "UE%d",ue+1);
        }
        else {
            printf(" ");
        }
        printf("%2.1f ", averages_table[ue]);
    }
    printf("\nAcquisition");
    printf("%*s",max_length-strlen("Acquisition")+1,"");
    if (ue_ac == 0) {
        printf("Aucune\n");
    }
    else {
        printf("%s\n", acquisition);
    }
    printf("Devenir%*s",max_length-strlen("Devenir")+1,"");
    if ((ue_ac / nbUE) <= 0.5) {
        printf("Redoublement\n");
    } else {
        printf("Passage\n");
    }
}

// GENERAL FUNCTIONS

/**
 * @brief Defines the number of UEs. Displays error messages if conditions are not met
 * @param f Definition of the number of UE
 */
void formation(Formation *f) {
    int nbUeDef;
    scanf("%d", &nbUeDef);
    if (f->nbUE == 0) {
        if (nbUeDef > MAX_UE || nbUeDef < MIN_UE) {
            printf("Le nombre d'UE est incorrect\n");
        } else {
            f->nbUE = nbUeDef;
            printf("Le nombre d'UE est defini\n");
        }
    } else {
        printf("Le nombre d'UE est deja defini\n");
    }
}

/**
 * @brief Add test entered by user
 * @param f Training studied + test added
 * @brief Displays messages if the adding is successful || if the conditions for adding are not met
 */
void epreuve(Formation *f) {
    unsigned int semester_number;
    unsigned char sub[MAX_CHAR];
    unsigned char epr[MAX_CHAR];
    float coef[MAX_UE];
    scanf("%d %s %s", &semester_number, &sub, &epr);
    for (int i = 0; i < f->nbUE; ++i) {
        scanf("%f", &coef[i]);
    }
    semester_number -= 1;
    if (f->nbUE == 0) {
        printf("Le nombre d'UE n'est pas defini\n");
    } else if (semester_number > 1 || semester_number < 0) {
        printf("Le numero de semestre est incorrect\n");
    } else if (test_exist_verification(f, semester_number, sub, epr) != -1) {
        printf("Une meme epreuve existe deja\n");
    } else if (impossible_coefficients_addition(f, coef)) {
        printf("Au moins un des coefficients est incorrect\n");
    } else {
        Semestre *s = &(f->semestres[semester_number]);
        int id_sub = subject_exist_verification(f, semester_number, sub);
        int idEp = 0;
        if (id_sub == -1) {
            id_sub = s->nbMatieres;
            printf("Matiere ajoutee a la formation\n");
            strcpy(s->matieres[id_sub].nomMatiere, sub);
            strcpy(s->matieres[id_sub].epreuves[idEp].nomEpreuve, epr);
            s->nbMatieres += 1;
        } else {
            idEp = s->matieres[id_sub].nbEpreuves;
            strcpy(s->matieres[id_sub].epreuves[idEp].nomEpreuve, epr);
        }
        s->matieres[id_sub].nbEpreuves += 1;
        for (int i = 0; i < f->nbUE; ++i) {
            s->matieres[id_sub].epreuves[idEp].coef[i] = coef[i];
        }
        printf("Epreuve ajoutee a la formation\n");
    }
}

/**
 * @brief Checks the training coefficients in parameter for a semester entered by the user
 * @param f Training studied
 * @brief Displays error messages if conditions are not met, and vice versa if not
 */
void coefficients(const Formation *f) {
    unsigned int semester_number;
    scanf("%d", &semester_number);
    semester_number -= 1;
    if (f->nbUE == 0) {
        printf("Le nombre d'UE n'est pas defini\n");
    } else if (semester_number > 1 || semester_number < 0) {
        printf("Le numero de semestre est incorrect\n");
    } else if (f->semestres[semester_number].nbMatieres == 0) {
        printf("Le semestre ne contient aucune epreuve\n");
    } else {
        if (incorrect_coefficients(f, semester_number)) {
            printf("Les coefficients d'au moins une UE de ce semestre sont tous nuls\n");
        } else {
            printf("Coefficients corrects\n");
        }
    }
}

/**
 * @brief Add a note
 * @param f Training studied
 * @brief Displays messages based on the validity of elements entered by the user, error messages otherwise
 */
void note(Formation *f) {
    unsigned int semester_number;
    char student_name[MAX_CHAR];
    char nomMat[MAX_CHAR];
    char nomEpr[MAX_CHAR];
    float note;
    scanf("%d %s %s %s %f", &semester_number, &student_name, &nomMat, &nomEpr, &note);
    semester_number -= 1;
    int id_sub = subject_exist_verification(f, semester_number, nomMat);
    int id_test = test_exist_verification(f, semester_number, nomMat, nomEpr);
    int id_student = student_exist_verification(f, student_name);
    if (semester_number > 1 || semester_number < 0) {
        printf("Le numero de semestre est incorrect");
    }
    else if (note > MAX_NOTE || MIN_NOTE > note) {
        printf("Note incorrecte\n");
    }
    else if (id_sub == -1) {
        printf("Matiere inconnue\n");
    }
    else if (id_test == -1) {
        printf("Epreuve inconnue\n");
    }
    else {
        unsigned int id_note = note_id(semester_number, id_sub, id_test);
        if (id_student == -1) {
            init_student(f, student_name);
            f->etudiant[f->nbETU].notes[id_note] = note;
            f->nbETU += 1;
            printf("Etudiant ajoute a la formation\n");
            printf("Note ajoutee a l'etudiant\n");
        } else {
            if (note_exist_verification(f, id_student, id_note)) {
                printf("Une note est deja definie pour l'etudiant\n");
            } else {
                f->etudiant[id_student].notes[id_note] = note;
                printf("Note ajoutee a l'etudiant\n");
            }
        }
    }
}

/**
 * @brief Checks the validity of a student's notes
 * @param f Training studied
 * @brief Displays error messages if conditions are not met, and vice versa if not
 */
void notes(const Formation *f) {
    unsigned int semester_number;
    char student_name[MAX_CHAR];
    scanf("%d %s", &semester_number, &student_name);
    semester_number -= 1;
    int id_student = student_exist_verification(f, student_name);
    if (semester_number > 1 || semester_number < 0) {
        printf("Le numero de semestre est incorrect\n");
    } else if (id_student == -1) {
        printf("Etudiant inconnu\n");
    } else {
        if (notes_id_student_exist_verification(f, id_student, semester_number)) {
            printf("Notes correctes\n");
        } else {
            printf("Il manque au moins une note pour cet etudiant\n");
        }
    }
}

/**
 * @brief Displays the semester 1 or 2 transcript of the entered student
 * @param f Training studied
 * @brief Displays error messages if the information is invalid, and vice versa otherwise
 */
void releve(const Formation *f) {
    unsigned int semester_number;
    char stu[MAX_CHAR];
    scanf("%d %s", &semester_number, &stu);
    semester_number -= 1;
    int id_student = student_exist_verification(f, stu);
    if (semester_number > 1 || semester_number < 0) {
        printf("Le numero de semestre est incorrect\n");
    } else if (incorrect_coefficients(f, semester_number)) {
        printf("Les coefficients de ce semestre sont incorrects\n");
    } else if (id_student == -1) {
        printf("Etudiant inconnu\n");
    } else if (!notes_id_student_exist_verification(f, id_student, semester_number)) {
        printf("Il manque au moins une note pour cet etudiant\n");
    } else {
        UE_averages_calculation(f, semester_number, id_student);
    }
}

/**
 * @brief Displays the decision of the jury in relation to the student entered
 * @param f Training studied
 * @brief Displays error messages if the data in the training structure is invalid or incomplete
 */
void decision(const Formation *f) {
    char stu[MAX_CHAR];
    scanf("%s", stu);
    int id_student = student_exist_verification(f, stu);
    if (id_student == -1) {
        printf("Etudiant inconnu\n");
    } else if (incorrect_coefficients(f, 0) || incorrect_coefficients(f, 1)) {
        printf("Les coefficients d'au moins un semestre sont incorrects\n");
    } else if (!notes_id_student_exist_verification(f, id_student, 0) || !notes_id_student_exist_verification(f, id_student, 1)) {
        printf("Il manque au moins une note pour cet etudiant\n");
    } else {
        float averages_table[f->nbUE];
        // Storing UE averages each semester
        year_averages_calculation(f, id_student, averages_table);
        final_decision_display(averages_table, f->nbUE);
    }
}

// MAIN

/**
 * @brief Here is the centerpiece
 */
int main() {
    char command[MAX_CHAR+1];
    Formation form;
    init_form(&form);
    do {
        scanf("%s", command);
        if (strcmp(command, "formation") == 0) formation(&form);
        else if (strcmp(command, "epreuve") == 0) epreuve(&form);
        else if (strcmp(command, "coefficients") == 0) coefficients(&form);
        else if (strcmp(command, "note") == 0) note(&form);
        else if (strcmp(command, "notes") == 0) notes(&form);
        else if (strcmp(command, "releve") == 0) releve(&form);
        else if (strcmp(command, "decision") == 0) decision(&form);
    } while (strcmp("exit", command) != 0);
}