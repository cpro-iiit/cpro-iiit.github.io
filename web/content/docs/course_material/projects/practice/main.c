#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 100
#define FILENAME "records.txt"
#define MAX_PROBLEMS 50
#define MAX_PROBLEM_TITLE 200
#define MAX_PROBLEM_DESC 1000
#define PROBLEMS_FILE "problems.txt"

typedef enum {
    GRADE_A,
    GRADE_B,
    GRADE_C,
    GRADE_D,
    GRADE_F
} Grade;

typedef enum {
    DIFFICULTY_EASY,
    DIFFICULTY_MEDIUM,
    DIFFICULTY_HARD
} Difficulty;

typedef struct {
    int id;
    char title[MAX_PROBLEM_TITLE];
    char description[MAX_PROBLEM_DESC];
    Difficulty difficulty;
    int pointsWorth;
} CodingProblem;

typedef struct {
    int studentRollNumber;
    int problemId;
    int pointsEarned;
    char submissionDate[20];
} Submission;

typedef struct {
    char name[MAX_NAME];
    int rollNumber;
    float marks;
    Grade grade;
    int problemsSolved;
    int totalPoints;
} Student;

typedef struct {
    Student *students;
    int count;
    int capacity;
    CodingProblem problems[MAX_PROBLEMS];
    int problemCount;
    Submission *submissions;
    int submissionCount;
    int submissionCapacity;
} StudentDatabase;

// Function prototypes
void initDatabase(StudentDatabase *db);
void freeDatabase(StudentDatabase *db);
void addStudent(StudentDatabase *db);
void deleteStudent(StudentDatabase *db);
void updateStudent(StudentDatabase *db);
void displayAllStudents(StudentDatabase *db);
void sortByMarks(StudentDatabase *db);
void calculateAverage(StudentDatabase *db);
Grade calculateGrade(float marks);
char gradeToChar(Grade grade);
Grade charToGrade(char c);
void saveToFile(StudentDatabase *db);
void loadFromFile(StudentDatabase *db);
void displayMenu();
void expandCapacity(StudentDatabase *db);

// Coding problems functions
void addCodingProblem(StudentDatabase *db);
void viewCodingProblems(StudentDatabase *db);
void submitSolution(StudentDatabase *db);
void viewStudentSubmissions(StudentDatabase *db);
void viewLeaderboard(StudentDatabase *db);
void problemsMenu(StudentDatabase *db);
char* difficultyToString(Difficulty diff);
Difficulty stringToDifficulty(char* str);
void saveProblemsToFile(StudentDatabase *db);
void loadProblemsFromFile(StudentDatabase *db);
void getCurrentDate(char* buffer);

int main() {
    StudentDatabase db;
    initDatabase(&db);
    loadFromFile(&db);
    loadProblemsFromFile(&db);
    
    int choice;
    
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch (choice) {
            case 1:
                addStudent(&db);
                break;
            case 2:
                deleteStudent(&db);
                break;
            case 3:
                updateStudent(&db);
                break;
            case 4:
                displayAllStudents(&db);
                break;
            case 5:
                sortByMarks(&db);
                printf("Students sorted by marks!\n");
                break;
            case 6:
                calculateAverage(&db);
                break;
            case 7:
                saveToFile(&db);
                break;
            case 8:
                loadFromFile(&db);
                break;
            case 9:
                problemsMenu(&db);
                break;
            case 10:
                saveToFile(&db);
                saveProblemsToFile(&db);
                printf("Data saved. Exiting...\n");
                freeDatabase(&db);
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\n");
    }
    
    return 0;
}

void initDatabase(StudentDatabase *db) {
    db->capacity = 10;
    db->count = 0;
    db->students = (Student *)malloc(db->capacity * sizeof(Student));
    if (db->students == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    db->problemCount = 0;
    db->submissionCapacity = 20;
    db->submissionCount = 0;
    db->submissions = (Submission *)malloc(db->submissionCapacity * sizeof(Submission));
    if (db->submissions == NULL) {
        printf("Memory allocation failed for submissions!\n");
        exit(1);
    }
}

void freeDatabase(StudentDatabase *db) {
    free(db->students);
    free(db->submissions);
    db->students = NULL;
    db->submissions = NULL;
    db->count = 0;
    db->capacity = 0;
    db->submissionCount = 0;
    db->submissionCapacity = 0;
}

void expandCapacity(StudentDatabase *db) {
    db->capacity *= 2;
    Student *temp = (Student *)realloc(db->students, db->capacity * sizeof(Student));
    if (temp == NULL) {
        printf("Memory reallocation failed!\n");
        exit(1);
    }
    db->students = temp;
}

void addStudent(StudentDatabase *db) {
    if (db->count >= db->capacity) {
        expandCapacity(db);
    }
    
    Student newStudent;
    
    printf("\n--- Add New Student ---\n");
    printf("Enter name: ");
    fgets(newStudent.name, MAX_NAME, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Remove newline
    
    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNumber);
    
    // Check for duplicate roll number
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].rollNumber == newStudent.rollNumber) {
            printf("Error: Roll number already exists!\n");
            getchar(); // Clear buffer
            return;
        }
    }
    
    printf("Enter marks (0-100): ");
    scanf("%f", &newStudent.marks);
    getchar(); // Clear newline
    
    if (newStudent.marks < 0 || newStudent.marks > 100) {
        printf("Invalid marks! Must be between 0 and 100.\n");
        return;
    }
    
    newStudent.grade = calculateGrade(newStudent.marks);
    newStudent.problemsSolved = 0;
    newStudent.totalPoints = 0;
    
    db->students[db->count] = newStudent;
    db->count++;
    
    printf("Student added successfully! Grade: %c\n", gradeToChar(newStudent.grade));
}

void deleteStudent(StudentDatabase *db) {
    if (db->count == 0) {
        printf("No students to delete!\n");
        return;
    }
    
    int rollNumber;
    printf("\n--- Delete Student ---\n");
    printf("Enter roll number to delete: ");
    scanf("%d", &rollNumber);
    getchar();
    
    int found = -1;
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].rollNumber == rollNumber) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Student with roll number %d not found!\n", rollNumber);
        return;
    }
    
    printf("Deleting: %s (Roll: %d)\n", db->students[found].name, db->students[found].rollNumber);
    
    // Shift elements left
    for (int i = found; i < db->count - 1; i++) {
        db->students[i] = db->students[i + 1];
    }
    
    db->count--;
    printf("Student deleted successfully!\n");
}

void updateStudent(StudentDatabase *db) {
    if (db->count == 0) {
        printf("No students to update!\n");
        return;
    }
    
    int rollNumber;
    printf("\n--- Update Student ---\n");
    printf("Enter roll number to update: ");
    scanf("%d", &rollNumber);
    getchar();
    
    int found = -1;
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].rollNumber == rollNumber) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Student with roll number %d not found!\n", rollNumber);
        return;
    }
    
    printf("Current details:\n");
    printf("Name: %s\n", db->students[found].name);
    printf("Marks: %.2f\n", db->students[found].marks);
    printf("Grade: %c\n", gradeToChar(db->students[found].grade));
    
    printf("\nEnter new name (or press Enter to keep current): ");
    char newName[MAX_NAME];
    fgets(newName, MAX_NAME, stdin);
    if (strlen(newName) > 1) {
        newName[strcspn(newName, "\n")] = 0;
        strcpy(db->students[found].name, newName);
    }
    
    printf("Enter new marks (or -1 to keep current): ");
    float newMarks;
    scanf("%f", &newMarks);
    getchar();
    
    if (newMarks >= 0 && newMarks <= 100) {
        db->students[found].marks = newMarks;
        db->students[found].grade = calculateGrade(newMarks);
    }
    
    printf("Student updated successfully! New grade: %c\n", gradeToChar(db->students[found].grade));
}

void displayAllStudents(StudentDatabase *db) {
    if (db->count == 0) {
        printf("\nNo students in database!\n");
        return;
    }
    
    printf("\n%-15s %-10s %-10s %-10s %-12s %-12s\n", "Name", "Roll No", "Marks", "Grade", "Problems", "Points");
    printf("-------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < db->count; i++) {
        printf("%-15s %-10d %-10.2f %-10c %-12d %-12d\n", 
               db->students[i].name,
               db->students[i].rollNumber,
               db->students[i].marks,
               gradeToChar(db->students[i].grade),
               db->students[i].problemsSolved,
               db->students[i].totalPoints);
    }
    printf("-------------------------------------------------------------------------------\n");
    printf("Total students: %d\n", db->count);
}

void sortByMarks(StudentDatabase *db) {
    if (db->count <= 1) {
        return;
    }
    
    // Bubble sort in descending order
    for (int i = 0; i < db->count - 1; i++) {
        for (int j = 0; j < db->count - i - 1; j++) {
            if (db->students[j].marks < db->students[j + 1].marks) {
                Student temp = db->students[j];
                db->students[j] = db->students[j + 1];
                db->students[j + 1] = temp;
            }
        }
    }
}

void calculateAverage(StudentDatabase *db) {
    if (db->count == 0) {
        printf("\nNo students in database!\n");
        return;
    }
    
    float sum = 0;
    float highest = db->students[0].marks;
    float lowest = db->students[0].marks;
    
    for (int i = 0; i < db->count; i++) {
        sum += db->students[i].marks;
        if (db->students[i].marks > highest) {
            highest = db->students[i].marks;
        }
        if (db->students[i].marks < lowest) {
            lowest = db->students[i].marks;
        }
    }
    
    float average = sum / db->count;
    
    printf("\n--- Class Statistics ---\n");
    printf("Total students: %d\n", db->count);
    printf("Average marks: %.2f\n", average);
    printf("Highest marks: %.2f\n", highest);
    printf("Lowest marks: %.2f\n", lowest);
    printf("Average grade: %c\n", gradeToChar(calculateGrade(average)));
}

Grade calculateGrade(float marks) {
    if (marks >= 90) return GRADE_A;
    else if (marks >= 80) return GRADE_B;
    else if (marks >= 70) return GRADE_C;
    else if (marks >= 60) return GRADE_D;
    else return GRADE_F;
}

char gradeToChar(Grade grade) {
    switch (grade) {
        case GRADE_A: return 'A';
        case GRADE_B: return 'B';
        case GRADE_C: return 'C';
        case GRADE_D: return 'D';
        case GRADE_F: return 'F';
        default: return 'F';
    }
}

Grade charToGrade(char c) {
    switch (c) {
        case 'A': return GRADE_A;
        case 'B': return GRADE_B;
        case 'C': return GRADE_C;
        case 'D': return GRADE_D;
        case 'F': return GRADE_F;
        default: return GRADE_F;
    }
}

void saveToFile(StudentDatabase *db) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    fprintf(file, "%d\n", db->count);
    
    for (int i = 0; i < db->count; i++) {
        fprintf(file, "%s\n", db->students[i].name);
        fprintf(file, "%d\n", db->students[i].rollNumber);
        fprintf(file, "%.2f\n", db->students[i].marks);
        fprintf(file, "%c\n", gradeToChar(db->students[i].grade));
        fprintf(file, "%d\n", db->students[i].problemsSolved);
        fprintf(file, "%d\n", db->students[i].totalPoints);
    }
    
    fclose(file);
    printf("Data saved to %s successfully!\n", FILENAME);
}

void loadFromFile(StudentDatabase *db) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No existing data file found. Starting with empty database.\n");
        return;
    }
    
    int count;
    if (fscanf(file, "%d\n", &count) != 1) {
        printf("Error reading file!\n");
        fclose(file);
        return;
    }
    
    // Clear existing data
    db->count = 0;
    
    // Ensure capacity
    while (db->capacity < count) {
        expandCapacity(db);
    }
    
    for (int i = 0; i < count; i++) {
        Student s;
        fgets(s.name, MAX_NAME, file);
        s.name[strcspn(s.name, "\n")] = 0;
        
        fscanf(file, "%d\n", &s.rollNumber);
        fscanf(file, "%f\n", &s.marks);
        
        char gradeChar;
        fscanf(file, " %c\n", &gradeChar);
        s.grade = charToGrade(gradeChar);
        
        fscanf(file, "%d\n", &s.problemsSolved);
        fscanf(file, "%d\n", &s.totalPoints);
        
        db->students[db->count++] = s;
    }
    
    fclose(file);
    printf("Loaded %d student(s) from %s\n", db->count, FILENAME);
}

void displayMenu() {
    printf("\n========================================\n");
    printf("  STUDENT RECORD MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Update Student\n");
    printf("4. Display All Students\n");
    printf("5. Sort by Marks\n");
    printf("6. Calculate Class Average\n");
    printf("7. Save to File\n");
    printf("8. Load from File\n");
    printf("9. Coding Problems Menu\n");
    printf("10. Exit\n");
    printf("========================================\n");
}

// Coding Problems Functions

void problemsMenu(StudentDatabase *db) {
    int choice;
    
    while (1) {
        printf("\n========================================\n");
        printf("     CODING PROBLEMS MENU\n");
        printf("========================================\n");
        printf("1. Add Coding Problem\n");
        printf("2. View All Problems\n");
        printf("3. Submit Solution\n");
        printf("4. View Student Submissions\n");
        printf("5. View Leaderboard\n");
        printf("6. Back to Main Menu\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                addCodingProblem(db);
                break;
            case 2:
                viewCodingProblems(db);
                break;
            case 3:
                submitSolution(db);
                break;
            case 4:
                viewStudentSubmissions(db);
                break;
            case 5:
                viewLeaderboard(db);
                break;
            case 6:
                return;
            default:
                printf("Invalid choice!\n");
        }
        printf("\n");
    }
}

void addCodingProblem(StudentDatabase *db) {
    if (db->problemCount >= MAX_PROBLEMS) {
        printf("Problem database is full!\n");
        return;
    }
    
    CodingProblem problem;
    
    printf("\n--- Add New Coding Problem ---\n");
    problem.id = db->problemCount + 1;
    
    printf("Enter problem title: ");
    fgets(problem.title, MAX_PROBLEM_TITLE, stdin);
    problem.title[strcspn(problem.title, "\n")] = 0;
    
    printf("Enter problem description: ");
    fgets(problem.description, MAX_PROBLEM_DESC, stdin);
    problem.description[strcspn(problem.description, "\n")] = 0;
    
    printf("Enter difficulty (1=Easy, 2=Medium, 3=Hard): ");
    int diff;
    scanf("%d", &diff);
    getchar();
    
    if (diff == 1) problem.difficulty = DIFFICULTY_EASY;
    else if (diff == 2) problem.difficulty = DIFFICULTY_MEDIUM;
    else if (diff == 3) problem.difficulty = DIFFICULTY_HARD;
    else {
        printf("Invalid difficulty!\n");
        return;
    }
    
    printf("Enter points worth: ");
    scanf("%d", &problem.pointsWorth);
    getchar();
    
    db->problems[db->problemCount] = problem;
    db->problemCount++;
    
    printf("Problem added successfully! ID: %d\n", problem.id);
}

void viewCodingProblems(StudentDatabase *db) {
    if (db->problemCount == 0) {
        printf("\nNo problems available!\n");
        return;
    }
    
    printf("\n%-5s %-30s %-15s %-10s\n", "ID", "Title", "Difficulty", "Points");
    printf("--------------------------------------------------------------\n");
    
    for (int i = 0; i < db->problemCount; i++) {
        printf("%-5d %-30s %-15s %-10d\n",
               db->problems[i].id,
               db->problems[i].title,
               difficultyToString(db->problems[i].difficulty),
               db->problems[i].pointsWorth);
    }
    printf("--------------------------------------------------------------\n");
    
    printf("\nView problem details? Enter problem ID (0 to skip): ");
    int id;
    scanf("%d", &id);
    getchar();
    
    if (id > 0 && id <= db->problemCount) {
        CodingProblem p = db->problems[id - 1];
        printf("\n--- Problem #%d ---\n", p.id);
        printf("Title: %s\n", p.title);
        printf("Difficulty: %s\n", difficultyToString(p.difficulty));
        printf("Points: %d\n", p.pointsWorth);
        printf("Description:\n%s\n", p.description);
    }
}

void submitSolution(StudentDatabase *db) {
    if (db->problemCount == 0) {
        printf("\nNo problems available to solve!\n");
        return;
    }
    
    if (db->count == 0) {
        printf("\nNo students registered!\n");
        return;
    }
    
    int rollNumber, problemId, pointsEarned;
    
    printf("\n--- Submit Solution ---\n");
    printf("Enter student roll number: ");
    scanf("%d", &rollNumber);
    
    // Find student
    int studentIndex = -1;
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].rollNumber == rollNumber) {
            studentIndex = i;
            break;
        }
    }
    
    if (studentIndex == -1) {
        printf("Student not found!\n");
        getchar();
        return;
    }
    
    printf("Enter problem ID: ");
    scanf("%d", &problemId);
    
    if (problemId < 1 || problemId > db->problemCount) {
        printf("Invalid problem ID!\n");
        getchar();
        return;
    }
    
    printf("Enter points earned (0-%d): ", db->problems[problemId - 1].pointsWorth);
    scanf("%d", &pointsEarned);
    getchar();
    
    if (pointsEarned < 0 || pointsEarned > db->problems[problemId - 1].pointsWorth) {
        printf("Invalid points!\n");
        return;
    }
    
    // Expand submissions array if needed
    if (db->submissionCount >= db->submissionCapacity) {
        db->submissionCapacity *= 2;
        Submission *temp = (Submission *)realloc(db->submissions, 
                                                 db->submissionCapacity * sizeof(Submission));
        if (temp == NULL) {
            printf("Memory reallocation failed!\n");
            return;
        }
        db->submissions = temp;
    }
    
    // Create submission
    Submission sub;
    sub.studentRollNumber = rollNumber;
    sub.problemId = problemId;
    sub.pointsEarned = pointsEarned;
    getCurrentDate(sub.submissionDate);
    
    db->submissions[db->submissionCount++] = sub;
    
    // Update student stats
    db->students[studentIndex].problemsSolved++;
    db->students[studentIndex].totalPoints += pointsEarned;
    
    printf("Solution submitted successfully!\n");
    printf("Student: %s | Total Points: %d | Problems Solved: %d\n",
           db->students[studentIndex].name,
           db->students[studentIndex].totalPoints,
           db->students[studentIndex].problemsSolved);
}

void viewStudentSubmissions(StudentDatabase *db) {
    if (db->submissionCount == 0) {
        printf("\nNo submissions yet!\n");
        return;
    }
    
    int rollNumber;
    printf("\n--- View Student Submissions ---\n");
    printf("Enter student roll number: ");
    scanf("%d", &rollNumber);
    getchar();
    
    // Find student
    int studentIndex = -1;
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].rollNumber == rollNumber) {
            studentIndex = i;
            break;
        }
    }
    
    if (studentIndex == -1) {
        printf("Student not found!\n");
        return;
    }
    
    printf("\nSubmissions for %s (Roll: %d)\n", 
           db->students[studentIndex].name, rollNumber);
    printf("%-10s %-30s %-15s %-15s\n", "Problem", "Title", "Points", "Date");
    printf("----------------------------------------------------------------------\n");
    
    int found = 0;
    for (int i = 0; i < db->submissionCount; i++) {
        if (db->submissions[i].studentRollNumber == rollNumber) {
            int probId = db->submissions[i].problemId - 1;
            printf("%-10d %-30s %-15d %-15s\n",
                   db->submissions[i].problemId,
                   db->problems[probId].title,
                   db->submissions[i].pointsEarned,
                   db->submissions[i].submissionDate);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No submissions found for this student.\n");
    } else {
        printf("----------------------------------------------------------------------\n");
        printf("Total Points: %d | Problems Solved: %d\n",
               db->students[studentIndex].totalPoints,
               db->students[studentIndex].problemsSolved);
    }
}

void viewLeaderboard(StudentDatabase *db) {
    if (db->count == 0) {
        printf("\nNo students to display!\n");
        return;
    }
    
    // Create a copy of students array for sorting
    Student *leaderboard = (Student *)malloc(db->count * sizeof(Student));
    for (int i = 0; i < db->count; i++) {
        leaderboard[i] = db->students[i];
    }
    
    // Sort by total points (descending)
    for (int i = 0; i < db->count - 1; i++) {
        for (int j = 0; j < db->count - i - 1; j++) {
            if (leaderboard[j].totalPoints < leaderboard[j + 1].totalPoints) {
                Student temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
    
    printf("\n========================================\n");
    printf("          CODING LEADERBOARD\n");
    printf("========================================\n");
    printf("%-5s %-15s %-10s %-12s %-12s\n", "Rank", "Name", "Roll No", "Problems", "Points");
    printf("--------------------------------------------------------------\n");
    
    for (int i = 0; i < db->count; i++) {
        printf("%-5d %-15s %-10d %-12d %-12d\n",
               i + 1,
               leaderboard[i].name,
               leaderboard[i].rollNumber,
               leaderboard[i].problemsSolved,
               leaderboard[i].totalPoints);
    }
    printf("--------------------------------------------------------------\n");
    
    free(leaderboard);
}

char* difficultyToString(Difficulty diff) {
    switch (diff) {
        case DIFFICULTY_EASY: return "Easy";
        case DIFFICULTY_MEDIUM: return "Medium";
        case DIFFICULTY_HARD: return "Hard";
        default: return "Unknown";
    }
}

Difficulty stringToDifficulty(char* str) {
    if (strcmp(str, "Easy") == 0) return DIFFICULTY_EASY;
    else if (strcmp(str, "Medium") == 0) return DIFFICULTY_MEDIUM;
    else if (strcmp(str, "Hard") == 0) return DIFFICULTY_HARD;
    return DIFFICULTY_EASY;
}

void getCurrentDate(char* buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void saveProblemsToFile(StudentDatabase *db) {
    FILE *file = fopen(PROBLEMS_FILE, "w");
    if (file == NULL) {
        printf("Error opening problems file for writing!\n");
        return;
    }
    
    fprintf(file, "%d\n", db->problemCount);
    
    for (int i = 0; i < db->problemCount; i++) {
        fprintf(file, "%d\n", db->problems[i].id);
        fprintf(file, "%s\n", db->problems[i].title);
        fprintf(file, "%s\n", db->problems[i].description);
        fprintf(file, "%s\n", difficultyToString(db->problems[i].difficulty));
        fprintf(file, "%d\n", db->problems[i].pointsWorth);
    }
    
    fprintf(file, "%d\n", db->submissionCount);
    for (int i = 0; i < db->submissionCount; i++) {
        fprintf(file, "%d %d %d %s\n",
                db->submissions[i].studentRollNumber,
                db->submissions[i].problemId,
                db->submissions[i].pointsEarned,
                db->submissions[i].submissionDate);
    }
    
    fclose(file);
    printf("Problems and submissions saved to %s\n", PROBLEMS_FILE);
}

void loadProblemsFromFile(StudentDatabase *db) {
    FILE *file = fopen(PROBLEMS_FILE, "r");
    if (file == NULL) {
        printf("No problems file found. Starting fresh.\n");
        return;
    }
    
    int count;
    if (fscanf(file, "%d\n", &count) != 1) {
        fclose(file);
        return;
    }
    
    db->problemCount = 0;
    for (int i = 0; i < count && i < MAX_PROBLEMS; i++) {
        CodingProblem p;
        fscanf(file, "%d\n", &p.id);
        fgets(p.title, MAX_PROBLEM_TITLE, file);
        p.title[strcspn(p.title, "\n")] = 0;
        fgets(p.description, MAX_PROBLEM_DESC, file);
        p.description[strcspn(p.description, "\n")] = 0;
        
        char diffStr[20];
        fgets(diffStr, 20, file);
        diffStr[strcspn(diffStr, "\n")] = 0;
        p.difficulty = stringToDifficulty(diffStr);
        
        fscanf(file, "%d\n", &p.pointsWorth);
        
        db->problems[db->problemCount++] = p;
    }
    
    int subCount;
    if (fscanf(file, "%d\n", &subCount) == 1) {
        db->submissionCount = 0;
        for (int i = 0; i < subCount; i++) {
            if (db->submissionCount >= db->submissionCapacity) {
                db->submissionCapacity *= 2;
                Submission *temp = (Submission *)realloc(db->submissions,
                                                         db->submissionCapacity * sizeof(Submission));
                if (temp) db->submissions = temp;
                else break;
            }
            
            Submission s;
            fscanf(file, "%d %d %d %s\n",
                   &s.studentRollNumber,
                   &s.problemId,
                   &s.pointsEarned,
                   s.submissionDate);
            db->submissions[db->submissionCount++] = s;
        }
    }
    
    fclose(file);
    printf("Loaded %d problem(s) and %d submission(s)\n", db->problemCount, db->submissionCount);
}