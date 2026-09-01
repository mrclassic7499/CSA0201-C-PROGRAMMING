/*
================================================================================
 PROJECT TITLE : Smart Emergency Resource Management and Analysis System
 COURSE        : Programming in C (Academic Project)
 COURSE OUTCOMES:
   - CO2: Operators, decision-making (if-else, switch-case), and loops (for, while)
   - CO3: Searching, sorting, merging, arrays, and string processing
   - CO5: Functions, recursion, pointers, and file handling
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RESOURCES 100
#define FILENAME "resources.txt"

// Structure definition for Resource record
struct Resource {
    int id;
    char name[50];
    char type[30];
    char department[30];
    int quantity;
    int threshold;
};

// Global array and resource counter
struct Resource resources[MAX_RESOURCES];
int resourceCount = 0;

// Status Constants
#define STATUS_CRITICAL 0
#define STATUS_LOW      1
#define STATUS_ADEQUATE 2

// Function Prototypes
void displayMainMenu();
void addResource();
void displayResources();
void updateResourceRecord(struct Resource *r); // Pointer usage
void updateResource();
void searchResource();
int recursiveSearchByID(struct Resource arr[], int count, int index, int targetId); // Recursion usage
void sortResources();
void swapResources(struct Resource *a, struct Resource *b); // Pointer usage
void mergeResources();
void analyseResources();
void generateReport();
void saveResources();
void loadResources();
void loadSampleData();
int getStatus(int quantity, int threshold);
const char* getStatusString(int status);
void clearInputBuffer();
void readString(const char *prompt, char *str, int size);

/*
 * Helper function to determine resource status
 * CO2 Demonstration: Decision making (if-else)
 * Logic:
 *   - quantity <= threshold / 2  -> CRITICAL
 *   - quantity <= threshold      -> LOW
 *   - else                       -> ADEQUATE
 */
int getStatus(int quantity, int threshold) {
    if (quantity <= threshold / 2) {
        return STATUS_CRITICAL;
    } else if (quantity <= threshold) {
        return STATUS_LOW;
    } else {
        return STATUS_ADEQUATE;
    }
}

// Convert status integer code to readable string representation
const char* getStatusString(int status) {
    switch (status) {
        case STATUS_CRITICAL: return "CRITICAL";
        case STATUS_LOW:      return "LOW";
        case STATUS_ADEQUATE: return "ADEQUATE";
        default:              return "UNKNOWN";
    }
}

// Clear input buffer to prevent stdin leftover newline issues
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Safely read string input from keyboard
void readString(const char *prompt, char *str, int size) {
    printf("%s", prompt);
    if (fgets(str, size, stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0'; // remove newline
        }
    }
}

/*
 * Pointer Demonstration 1: Pass structure pointer to modify contents
 * CO5 Demonstration: Pointers used to modify struct fields directly in memory
 */
void updateResourceRecord(struct Resource *r) {
    // Pointer usage: 'r' is a pointer to struct Resource.
    // Arrow operator (->) dereferences pointer and accesses struct fields.
    printf("\nUpdating Resource ID: %d (%s)\n", r->id, r->name);
    
    char inputBuffer[50];
    
    printf("Enter New Name (press Enter to keep '%s'): ", r->name);
    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL) {
        size_t len = strlen(inputBuffer);
        if (len > 0 && inputBuffer[len - 1] == '\n') inputBuffer[len - 1] = '\0';
        if (strlen(inputBuffer) > 0) {
            strcpy(r->name, inputBuffer);
        }
    }

    printf("Enter New Type (press Enter to keep '%s'): ", r->type);
    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL) {
        size_t len = strlen(inputBuffer);
        if (len > 0 && inputBuffer[len - 1] == '\n') inputBuffer[len - 1] = '\0';
        if (strlen(inputBuffer) > 0) {
            strcpy(r->type, inputBuffer);
        }
    }

    printf("Enter New Department (press Enter to keep '%s'): ", r->department);
    if (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL) {
        size_t len = strlen(inputBuffer);
        if (len > 0 && inputBuffer[len - 1] == '\n') inputBuffer[len - 1] = '\0';
        if (strlen(inputBuffer) > 0) {
            strcpy(r->department, inputBuffer);
        }
    }

    printf("Enter New Quantity (current %d, enter -1 to keep): ", r->quantity);
    int newQty;
    if (scanf("%d", &newQty) == 1) {
        clearInputBuffer();
        if (newQty >= 0) {
            r->quantity = newQty;
        }
    } else {
        clearInputBuffer();
    }

    printf("Enter New Minimum Threshold (current %d, enter -1 to keep): ", r->threshold);
    int newThresh;
    if (scanf("%d", &newThresh) == 1) {
        clearInputBuffer();
        if (newThresh > 0) {
            r->threshold = newThresh;
        }
    } else {
        clearInputBuffer();
    }

    printf("\n[SUCCESS] Resource ID %d updated successfully!\n", r->id);
    printf("Updated Status: %s\n", getStatusString(getStatus(r->quantity, r->threshold)));
}

/*
 * Pointer Demonstration 2: Swap two Resource structs using pointers
 * CO5 Demonstration: Pointers used in sorting algorithm
 */
void swapResources(struct Resource *a, struct Resource *b) {
    struct Resource temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Recursion Demonstration: Recursive search function for Resource ID
 * CO5 Demonstration: Function calling itself with reduced problem size
 */
int recursiveSearchByID(struct Resource arr[], int count, int index, int targetId) {
    // Recursion is demonstrated here
    // Base Case 1: Out of array bounds -> Not found
    if (index >= count) {
        return -1;
    }
    // Base Case 2: Target ID matched at current index -> Found
    if (arr[index].id == targetId) {
        return index;
    }
    // Recursive Step: Search remaining array starting from index + 1
    return recursiveSearchByID(arr, count, index + 1, targetId);
}

// 1. Add Resource
void addResource() {
    printf("\n==================================================\n");
    printf("                  ADD NEW RESOURCE                \n");
    printf("==================================================\n");

    if (resourceCount >= MAX_RESOURCES) {
        printf("[ERROR] Capacity full! Cannot add more resources.\n");
        return;
    }

    int id;
    printf("Enter Resource ID: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERROR] Invalid input for ID!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (id <= 0) {
        printf("[ERROR] Resource ID must be a positive integer!\n");
        return;
    }

    // CO3 & CO5: Use recursive search to check for duplicate ID
    int existingIndex = recursiveSearchByID(resources, resourceCount, 0, id);
    if (existingIndex != -1) {
        printf("[ERROR] Duplicate Resource ID! ID %d already exists (%s).\n", id, resources[existingIndex].name);
        return;
    }

    struct Resource newRes;
    newRes.id = id;

    readString("Enter Resource Name: ", newRes.name, sizeof(newRes.name));
    if (strlen(newRes.name) == 0) {
        printf("[ERROR] Resource Name cannot be empty!\n");
        return;
    }

    readString("Enter Resource Type (e.g. Medicine, Equipment, Bed, Supply): ", newRes.type, sizeof(newRes.type));
    if (strlen(newRes.type) == 0) {
        printf("[ERROR] Resource Type cannot be empty!\n");
        return;
    }

    readString("Enter Department (e.g. Emergency, ICU, Surgery, Pharmacy): ", newRes.department, sizeof(newRes.department));
    if (strlen(newRes.department) == 0) {
        printf("[ERROR] Department cannot be empty!\n");
        return;
    }

    printf("Enter Quantity: ");
    if (scanf("%d", &newRes.quantity) != 1 || newRes.quantity < 0) {
        printf("[ERROR] Quantity must be a non-negative integer!\n");
        clearInputBuffer();
        return;
    }

    printf("Enter Minimum Threshold: ");
    if (scanf("%d", &newRes.threshold) != 1 || newRes.threshold <= 0) {
        printf("[ERROR] Minimum Threshold must be a positive integer!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // Store in global array
    resources[resourceCount++] = newRes;

    int status = getStatus(newRes.quantity, newRes.threshold);
    printf("\n[SUCCESS] Resource '%s' (ID: %d) added successfully!\n", newRes.name, newRes.id);
    printf("Initial Resource Status: %s\n", getStatusString(status));
}

// 2. Display Resources
void displayResources() {
    printf("\n==================================================================================================\n");
    printf("                                   CURRENT EMERGENCY RESOURCES                                    \n");
    printf("==================================================================================================\n");

    if (resourceCount == 0) {
        printf("No resource records found in the system.\n");
        printf("==================================================================================================\n");
        return;
    }

    printf("%-6s %-22s %-15s %-15s %-8s %-11s %-10s\n", "ID", "Name", "Type", "Department", "Qty", "Threshold", "Status");
    printf("--------------------------------------------------------------------------------------------------\n");

    // CO2: Loop through array and print formatted output
    for (int i = 0; i < resourceCount; i++) {
        int status = getStatus(resources[i].quantity, resources[i].threshold);
        printf("%-6d %-22s %-15s %-15s %-8d %-11d %-10s\n",
               resources[i].id,
               resources[i].name,
               resources[i].type,
               resources[i].department,
               resources[i].quantity,
               resources[i].threshold,
               getStatusString(status));
    }
    printf("==================================================================================================\n");
    printf("Total Records Displayed: %d\n", resourceCount);
}

// 3. Update Resource
void updateResource() {
    printf("\n==================================================\n");
    printf("                  UPDATE RESOURCE                 \n");
    printf("==================================================\n");

    if (resourceCount == 0) {
        printf("No resources available to update.\n");
        return;
    }

    int id;
    printf("Enter Resource ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERROR] Invalid ID input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // CO5 Demonstration: Call recursive search function
    int index = recursiveSearchByID(resources, resourceCount, 0, id);
    if (index == -1) {
        printf("[ERROR] Resource with ID %d not found!\n", id);
        return;
    }

    // CO5 Demonstration: Pass address of resource struct to pointer function
    updateResourceRecord(&resources[index]);
}

// 4. Search Resource
void searchResource() {
    printf("\n==================================================\n");
    printf("                  SEARCH RESOURCE                 \n");
    printf("==================================================\n");

    if (resourceCount == 0) {
        printf("No resources available to search.\n");
        return;
    }

    printf("Search By:\n");
    printf("1. Resource ID (Using Recursive Search)\n");
    printf("2. Resource Name (Using Linear String Search)\n");
    printf("Enter choice (1-2): ");

    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("[ERROR] Invalid option!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (choice == 1) {
        int id;
        printf("Enter Resource ID: ");
        if (scanf("%d", &id) != 1) {
            printf("[ERROR] Invalid ID!\n");
            clearInputBuffer();
            return;
        }
        clearInputBuffer();

        // Recursion is demonstrated here
        int index = recursiveSearchByID(resources, resourceCount, 0, id);
        if (index != -1) {
            printf("\n[RESULT] Resource Found!\n");
            printf("--------------------------------------------------------------------------------------------------\n");
            printf("%-6s %-22s %-15s %-15s %-8s %-11s %-10s\n", "ID", "Name", "Type", "Department", "Qty", "Threshold", "Status");
            printf("--------------------------------------------------------------------------------------------------\n");
            int st = getStatus(resources[index].quantity, resources[index].threshold);
            printf("%-6d %-22s %-15s %-15s %-8d %-11d %-10s\n",
                   resources[index].id, resources[index].name, resources[index].type,
                   resources[index].department, resources[index].quantity,
                   resources[index].threshold, getStatusString(st));
            printf("--------------------------------------------------------------------------------------------------\n");
        } else {
            printf("\n[RESULT] Resource ID %d not found in system.\n", id);
        }
    } else if (choice == 2) {
        char searchName[50];
        readString("Enter Resource Name or Substring to search: ", searchName, sizeof(searchName));

        int foundCount = 0;
        printf("\n[RESULT] Matching Resources:\n");
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("%-6s %-22s %-15s %-15s %-8s %-11s %-10s\n", "ID", "Name", "Type", "Department", "Qty", "Threshold", "Status");
        printf("--------------------------------------------------------------------------------------------------\n");

        // CO3: Linear search and string matching using strstr / strcmp
        for (int i = 0; i < resourceCount; i++) {
            if (strstr(resources[i].name, searchName) != NULL) {
                int st = getStatus(resources[i].quantity, resources[i].threshold);
                printf("%-6d %-22s %-15s %-15s %-8d %-11d %-10s\n",
                       resources[i].id, resources[i].name, resources[i].type,
                       resources[i].department, resources[i].quantity,
                       resources[i].threshold, getStatusString(st));
                foundCount++;
            }
        }
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("Total matches found: %d\n", foundCount);
    } else {
        printf("[ERROR] Invalid choice!\n");
    }
}

// 5. Sort Resources
void sortResources() {
    printf("\n==================================================\n");
    printf("                  SORT RESOURCES                  \n");
    printf("==================================================\n");

    if (resourceCount <= 1) {
        printf("Not enough records to sort.\n");
        return;
    }

    printf("Sort Options:\n");
    printf("1. Sort by Resource ID (Ascending)\n");
    printf("2. Sort by Resource Name (Alphabetical)\n");
    printf("3. Sort by Quantity (Ascending)\n");
    printf("4. Sort by Status (Critical -> Low -> Adequate)\n");
    printf("Enter choice (1-4): ");

    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("[ERROR] Invalid option!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // CO3 Demonstration: Bubble Sort algorithm implementation
    for (int i = 0; i < resourceCount - 1; i++) {
        for (int j = 0; j < resourceCount - i - 1; j++) {
            int shouldSwap = 0;

            switch (choice) {
                case 1:
                    if (resources[j].id > resources[j + 1].id) shouldSwap = 1;
                    break;
                case 2:
                    if (strcmp(resources[j].name, resources[j + 1].name) > 0) shouldSwap = 1;
                    break;
                case 3:
                    if (resources[j].quantity > resources[j + 1].quantity) shouldSwap = 1;
                    break;
                case 4: {
                    int statusA = getStatus(resources[j].quantity, resources[j].threshold);
                    int statusB = getStatus(resources[j + 1].quantity, resources[j + 1].threshold);
                    if (statusA > statusB) shouldSwap = 1;
                    break;
                }
                default:
                    printf("[ERROR] Invalid sort choice!\n");
                    return;
            }

            // CO5 Demonstration: Swap using pointers
            if (shouldSwap) {
                swapResources(&resources[j], &resources[j + 1]);
            }
        }
    }

    printf("\n[SUCCESS] Resources sorted successfully!\n");
    displayResources();
}

// 6. Merge Department Records
void mergeResources() {
    printf("\n==================================================\n");
    printf("             MERGE DEPARTMENT RECORDS             \n");
    printf("==================================================\n");

    int numIncoming;
    printf("Enter number of incoming department records to merge: ");
    if (scanf("%d", &numIncoming) != 1 || numIncoming <= 0) {
        printf("[ERROR] Invalid number of records!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int newAdded = 0;
    int duplicatesUpdated = 0;

    printf("\nMerging department records...\n");

    for (int k = 0; k < numIncoming; k++) {
        printf("\n--- Incoming Record %d of %d ---\n", k + 1, numIncoming);
        
        struct Resource incoming;
        printf("Enter Resource ID: ");
        if (scanf("%d", &incoming.id) != 1 || incoming.id <= 0) {
            printf("[ERROR] Invalid ID! Skipping record.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        readString("Enter Resource Name: ", incoming.name, sizeof(incoming.name));
        readString("Enter Resource Type: ", incoming.type, sizeof(incoming.type));
        readString("Enter Department: ", incoming.department, sizeof(incoming.department));

        printf("Enter Quantity: ");
        if (scanf("%d", &incoming.quantity) != 1 || incoming.quantity < 0) {
            printf("[ERROR] Invalid Quantity! Skipping record.\n");
            clearInputBuffer();
            continue;
        }

        printf("Enter Minimum Threshold: ");
        if (scanf("%d", &incoming.threshold) != 1 || incoming.threshold <= 0) {
            printf("[ERROR] Invalid Threshold! Skipping record.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        // CO3: Check if ID already exists (Array Merging & Duplicate handling)
        int existingIndex = recursiveSearchByID(resources, resourceCount, 0, incoming.id);
        if (existingIndex != -1) {
            // CO3: Update existing resource quantity
            resources[existingIndex].quantity += incoming.quantity;
            duplicatesUpdated++;
            printf("[INFO] Duplicate Resource ID %d found. Added %d units to existing record '%s'. New Qty: %d\n",
                   incoming.id, incoming.quantity, resources[existingIndex].name, resources[existingIndex].quantity);
        } else {
            // Add as new resource
            if (resourceCount < MAX_RESOURCES) {
                resources[resourceCount++] = incoming;
                newAdded++;
                printf("[INFO] New Resource ID %d ('%s') added to system inventory.\n", incoming.id, incoming.name);
            } else {
                printf("[ERROR] Inventory full! Cannot add Resource ID %d.\n", incoming.id);
            }
        }
    }

    printf("\n==================================================\n");
    printf("New resources added            : %d\n", newAdded);
    printf("Duplicate resources found      : %d\n", duplicatesUpdated);
    printf("Duplicate quantities updated successfully.\n");
    printf("Merge completed!\n");
    printf("==================================================\n");
}

// 7. Resource Analysis
void analyseResources() {
    printf("\n==================================================\n");
    printf("               RESOURCE ANALYSIS                  \n");
    printf("==================================================\n");

    if (resourceCount == 0) {
        printf("No resources available for analysis.\n");
        return;
    }

    int totalQuantity = 0;
    int countAdequate = 0;
    int countLow = 0;
    int countCritical = 0;

    // CO2 & CO3: Loop and aggregate analytical data
    for (int i = 0; i < resourceCount; i++) {
        totalQuantity += resources[i].quantity;
        int st = getStatus(resources[i].quantity, resources[i].threshold);
        if (st == STATUS_CRITICAL) countCritical++;
        else if (st == STATUS_LOW) countLow++;
        else countAdequate++;
    }

    printf("Total Resource Types : %d\n", resourceCount);
    printf("Total Quantity       : %d units\n\n", totalQuantity);
    printf("Adequate Resources   : %d\n", countAdequate);
    printf("Low Resources        : %d\n", countLow);
    printf("Critical Resources   : %d\n", countCritical);

    printf("\n--------------------------------------------------\n");
    printf("Resources Requiring Immediate Replenishment:\n");
    printf("--------------------------------------------------\n");
    int replenishCount = 0;
    for (int i = 0; i < resourceCount; i++) {
        int st = getStatus(resources[i].quantity, resources[i].threshold);
        if (st == STATUS_CRITICAL || st == STATUS_LOW) {
            printf("%-6d - %-22s (%-10s) [Qty: %d, Threshold: %d]\n",
                   resources[i].id, resources[i].name, getStatusString(st),
                   resources[i].quantity, resources[i].threshold);
            replenishCount++;
        }
    }
    if (replenishCount == 0) {
        printf("None! All resources are currently ADEQUATE.\n");
    }

    printf("\n--------------------------------------------------\n");
    printf("DEPARTMENT-WISE AVAILABILITY:\n");
    printf("--------------------------------------------------\n");
    
    // Aggregate department wise quantity
    char departments[MAX_RESOURCES][30];
    int deptQty[MAX_RESOURCES] = {0};
    int deptCount = 0;

    for (int i = 0; i < resourceCount; i++) {
        int found = -1;
        for (int d = 0; d < deptCount; d++) {
            if (strcmp(departments[d], resources[i].department) == 0) {
                found = d;
                break;
            }
        }
        if (found != -1) {
            deptQty[found] += resources[i].quantity;
        } else {
            strcpy(departments[deptCount], resources[i].department);
            deptQty[deptCount] = resources[i].quantity;
            deptCount++;
        }
    }

    for (int d = 0; d < deptCount; d++) {
        printf("%-15s : %d units\n", departments[d], deptQty[d]);
    }
    printf("==================================================\n");
}

// 8. Generate Consolidated Report
void generateReport() {
    printf("\n==================================================================================================\n");
    printf("                         CONSOLIDATED EMERGENCY RESOURCE MANAGEMENT REPORT                        \n");
    printf("==================================================================================================\n");

    if (resourceCount == 0) {
        printf("System contains no data to generate report.\n");
        return;
    }

    int totalQty = 0, critical = 0, low = 0, adequate = 0;
    for (int i = 0; i < resourceCount; i++) {
        totalQty += resources[i].quantity;
        int st = getStatus(resources[i].quantity, resources[i].threshold);
        if (st == STATUS_CRITICAL) critical++;
        else if (st == STATUS_LOW) low++;
        else adequate++;
    }

    printf("\n1. OVERVIEW & SUMMARY STATISTICS:\n");
    printf("   - Total Resource Categories : %d\n", resourceCount);
    printf("   - Total Inventory Volume    : %d units\n", totalQty);
    printf("   - Adequate Stock Items      : %d\n", adequate);
    printf("   - Low Stock Items           : %d\n", low);
    printf("   - Critical Stock Items      : %d\n", critical);

    printf("\n2. COMPLETE RESOURCE INVENTORY:\n");
    printf("%-6s %-22s %-15s %-15s %-8s %-11s %-10s\n", "ID", "Name", "Type", "Department", "Qty", "Threshold", "Status");
    printf("--------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < resourceCount; i++) {
        int st = getStatus(resources[i].quantity, resources[i].threshold);
        printf("%-6d %-22s %-15s %-15s %-8d %-11d %-10s\n",
               resources[i].id, resources[i].name, resources[i].type,
               resources[i].department, resources[i].quantity,
               resources[i].threshold, getStatusString(st));
    }

    printf("\n3. CRITICAL ACTION REQUIRED (REPLENISHMENT LIST):\n");
    int actionRequired = 0;
    for (int i = 0; i < resourceCount; i++) {
        int st = getStatus(resources[i].quantity, resources[i].threshold);
        if (st == STATUS_CRITICAL || st == STATUS_LOW) {
            printf("   * ID %-4d: %-20s [%-10s] Current Qty: %-4d (Min Threshold: %d)\n",
                   resources[i].id, resources[i].name, getStatusString(st),
                   resources[i].quantity, resources[i].threshold);
            actionRequired++;
        }
    }
    if (actionRequired == 0) {
        printf("   No urgent replenishment required.\n");
    }

    printf("\n==================================================================================================\n");
    printf("                                     END OF REPORT                                                \n");
    printf("==================================================================================================\n");
}

// 9. Save Resources to File
void saveResources() {
    printf("\n==================================================\n");
    printf("                  SAVE RESOURCES                  \n");
    printf("==================================================\n");

    // CO5 Demonstration: File Handling using fopen, fprintf, fclose
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("[ERROR] Failed to open file '%s' for writing!\n", FILENAME);
        return;
    }

    for (int i = 0; i < resourceCount; i++) {
        fprintf(file, "%d|%s|%s|%s|%d|%d\n",
                resources[i].id,
                resources[i].name,
                resources[i].type,
                resources[i].department,
                resources[i].quantity,
                resources[i].threshold);
    }

    fclose(file);
    printf("[SUCCESS] %d resource records saved successfully to '%s'!\n", resourceCount, FILENAME);
}

// 10. Load Resources from File
void loadResources() {
    printf("\n==================================================\n");
    printf("                  LOAD RESOURCES                  \n");
    printf("==================================================\n");

    // CO5 Demonstration: File Handling using fopen, fscanf/fgets, fclose
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("[WARNING] File '%s' not found!\n", FILENAME);
        printf("Loading standard sample data instead...\n");
        loadSampleData();
        return;
    }

    resourceCount = 0;
    char line[200];
    while (fgets(line, sizeof(line), file) != NULL && resourceCount < MAX_RESOURCES) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';
        if (strlen(line) == 0) continue;

        struct Resource r;
        // Parse pipe-delimited string format
        if (sscanf(line, "%d|%49[^|]|%29[^|]|%29[^|]|%d|%d",
                   &r.id, r.name, r.type, r.department, &r.quantity, &r.threshold) == 6) {
            resources[resourceCount++] = r;
        }
    }

    fclose(file);
    printf("[SUCCESS] %d resource records loaded successfully from '%s'!\n", resourceCount, FILENAME);
}

// Pre-populate sample records if file doesn't exist
void loadSampleData() {
    struct Resource sample[] = {
        {101, "Paracetamol", "Medicine", "Emergency", 500, 100},
        {102, "Ventilator", "Equipment", "ICU", 2, 5},
        {103, "Emergency Bed", "Bed", "Emergency", 4, 5},
        {104, "Oxygen Cylinder", "Supply", "ICU", 20, 10},
        {105, "Surgical Gloves", "Supply", "Surgery", 300, 100},
        {106, "Defibrillator", "Equipment", "ICU", 1, 4},
        {107, "IV Saline 500ml", "Medicine", "Emergency", 40, 100},
        {108, "N95 Masks", "Supply", "Pharmacy", 150, 50},
        {109, "Morphine Injection", "Medicine", "Pharmacy", 15, 10},
        {110, "Stretcher", "Equipment", "Emergency", 3, 8}
    };
    int sampleSize = sizeof(sample) / sizeof(sample[0]);

    resourceCount = 0;
    for (int i = 0; i < sampleSize && i < MAX_RESOURCES; i++) {
        resources[resourceCount++] = sample[i];
    }
    printf("[INFO] 10 sample emergency resources loaded successfully!\n");
}

// Display Main Menu UI
void displayMainMenu() {
    printf("\n==================================================\n");
    printf("   SMART EMERGENCY RESOURCE MANAGEMENT SYSTEM     \n");
    printf("==================================================\n");
    printf(" 1. Add Resource\n");
    printf(" 2. Display Resources\n");
    printf(" 3. Update Resource\n");
    printf(" 4. Search Resource\n");
    printf(" 5. Sort Resources\n");
    printf(" 6. Merge Department Records\n");
    printf(" 7. Analyse Resources\n");
    printf(" 8. Generate Report\n");
    printf(" 9. Save Resources\n");
    printf("10. Load Resources\n");
    printf("11. Exit\n");
    printf("==================================================\n");
    printf("Enter your choice (1-11): ");
}

int main() {
    printf("Initializing Smart Emergency Resource Management System...\n");
    
    // Automatically load data from file or sample data on startup
    loadResources();

    int choice;
    do {
        displayMainMenu();
        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid choice! Please enter a number between 1 and 11.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        // CO2 Demonstration: Switch-Case Menu Selection
        switch (choice) {
            case 1:  addResource(); break;
            case 2:  displayResources(); break;
            case 3:  updateResource(); break;
            case 4:  searchResource(); break;
            case 5:  sortResources(); break;
            case 6:  mergeResources(); break;
            case 7:  analyseResources(); break;
            case 8:  generateReport(); break;
            case 9:  saveResources(); break;
            case 10: loadResources(); break;
            case 11:
                printf("\nSaving resources before exiting...\n");
                saveResources();
                printf("\nThank you for using Smart Emergency Resource Management System!\nExiting...\n");
                break;
            default:
                printf("[ERROR] Invalid choice! Option must be between 1 and 11.\n");
                break;
        }

    } while (choice != 11);

    return 0;
}
