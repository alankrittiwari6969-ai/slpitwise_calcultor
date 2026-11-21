   #include <stdio.h>
 
   double add(double a, double b) {
       return a + b;
   }
 
   double subtract(double a, double b) {
       return a - b;
   }
 
   double multiply(double a, double b) {
       return a * b;
   }
 
   double divide(double a, double b) {
       return a / b;
   }
   #define MAX_PEOPLE 10

typedef struct {
    char name[30];
    double paid;
    double balance;
} Person;


void splitwise(void) {
    Person people[MAX_PEOPLE];
    int n;
    double total = 0, share;

    printf("How many people (2-%d)? ", MAX_PEOPLE);
    scanf("%d", &n);
    if (n < 2 || n > MAX_PEOPLE) {
        printf("Invalid number of people!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Name of person %d: ", i + 1);
        scanf("%29s", people[i].name);
        printf("How much did %s pay? ", people[i].name);
        scanf("%lf", &people[i].paid);
        total += people[i].paid;
    }

    share = total / n;
    printf("\nTotal = %.2f, each share = %.2f\n", total, share);

    for (int i = 0; i < n; i++) {
        people[i].balance = people[i].paid - share;
    }

    printf("\n--- Who pays whom ---\n");
    int settled = 0;

    while (1) {
        int maxIdx = 0, minIdx = 0;
        for (int i = 1; i < n; i++) {
            if (people[i].balance > people[maxIdx].balance) maxIdx = i;
            if (people[i].balance < people[minIdx].balance) minIdx = i;
        }

        Person *creditor = &people[maxIdx];
        Person *debtor = &people[minIdx];

        if (creditor->balance < 0.01) break;

        double amount = creditor->balance;
        if (-debtor->balance < amount) amount = -debtor->balance;

        printf("%s pays %s: %.2f\n", debtor->name, creditor->name, amount);
        creditor->balance -= amount;
        debtor->balance += amount;
        settled = 1;
    }

    if (!settled) printf("Everyone is already settled!\n");
}
 
   int main(void) {
    int choice;
    double x, y;

    do {
        printf("\n=== CCALC ===\n");
        printf("1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Splitwise\n0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        if (choice == 5) {
            splitwise();
            continue;
        }

        printf("Enter two numbers: ");
        scanf("%lf %lf", &x, &y);

        switch (choice) {
            case 1:
                printf("Result = %.2f\n", add(x, y));
                break;
            case 2:
                printf("Result = %.2f\n", subtract(x, y));
                break;
            case 3:
                printf("Result = %.2f\n", multiply(x, y));
                break;
            case 4:
                if (y == 0) {
                    printf("Cannot divide by zero!\n");
                } else {
                    printf("Result = %.2f\n", divide(x, y));
                }
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    printf("Bye!\n");
    return 0;
}