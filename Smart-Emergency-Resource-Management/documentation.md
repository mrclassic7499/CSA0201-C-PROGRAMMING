# Academic Project Documentation

## Title
**Smart Emergency Resource Management and Analysis System using C**

---

## 1. Problem Statement
Hospital emergency departments and Intensive Care Units (ICUs) deal with life-critical situations where delays in procuring essential medical supplies (such as ventilators, oxygen cylinders, stretchers, defibrillators, and emergency medicines) can lead to adverse patient outcomes. Traditional manual logbooks or fragmented spreadsheet tracking often suffer from delayed stock updates, lack of automated threshold alerts, risk of duplicate entries during multi-department transfers, and high risk of data loss.

To solve this problem, the **Smart Emergency Resource Management and Analysis System** is developed as a lightweight, menu-driven C programming application. It enables hospital administrators to add, update, display, search, sort, merge, analyze, and save emergency resource records in real time.

---

## 2. Project Objectives
* **Automated Stock Status Classification**: Automatically classify every resource as `CRITICAL`, `LOW`, or `ADEQUATE` based on its current quantity relative to its minimum threshold.
* **Efficient Inventory Operations**: Provide administrative functions to Add, Display, Update, Search, and Sort resources.
* **Multi-Department Data Merging**: Merge incoming stock records from secondary departments (e.g., ICU, Surgery, Pharmacy) into the emergency inventory without introducing duplicate IDs.
* **Real-Time Analytics & Reporting**: Generate statistical summaries of total inventory volume, critical items requiring urgent replenishment, and department-wise availability.
* **Persistent File Storage**: Implement file I/O operations to save and load resource data permanently in `resources.txt`.

---

## 3. Course Outcomes (CO) Mapping

| Course Outcome | Description | Demonstrated In Code |
| :--- | :--- | :--- |
| **CO2** | Operators, decision-making, and looping constructs | `if-else` decision blocks in `getStatus()`, `switch-case` in `main()` menu driver, `for` and `while` loops for array iteration and buffer clearing. |
| **CO3** | Searching, sorting, merging, arrays, and string processing | Global structure array `resources[MAX_RESOURCES]`, string functions (`strcmp`, `strcpy`, `strlen`, `strstr`), Bubble Sort in `sortResources()`, array merging & duplicate quantity aggregation in `mergeResources()`. |
| **CO5** | Functions, recursion, pointers, and file handling | User-defined functions (`addResource`, `displayResources`, etc.), recursive search in `recursiveSearchByID()`, pointer mutation in `updateResourceRecord(struct Resource *r)` and `swapResources(struct Resource *a, struct Resource *b)`, file I/O in `saveResources()` and `loadResources()`. |

---

## 4. Sustainable Development Goals (SDG) Mapping

* **SDG 3: Good Health and Well-Being** — Ensures hospital emergency departments maintain continuous availability of life-saving medical supplies and equipment, preventing critical shortages during medical emergencies.
* **SDG 9: Industry, Innovation and Infrastructure** — Enhances hospital operational infrastructure through automated digital tracking, real-time inventory analytics, and structured data handling.
* **SDG 11: Sustainable Cities and Communities** — Strengthens urban emergency healthcare readiness and disaster preparedness.

---

## 5. System Features
1. **Menu-Driven Interface**: 11 clean options managed by `switch-case` and a `do-while` loop.
2. **Add Resource**: Adds new records with strict duplicate ID and positive threshold validation.
3. **Display Resources**: Formatted table view showing ID, Name, Type, Department, Quantity, Threshold, and Status.
4. **Update Resource**: Searches by ID and updates struct fields via structure pointers (`struct Resource *r`).
5. **Search Resource**:
   - ID Search: Uses a **recursive search algorithm** (`recursiveSearchByID`).
   - Name Search: Uses linear string matching (`strstr`).
6. **Sort Resources**: Bubble Sort supporting sorting by ID, Name, Quantity, or Status.
7. **Merge Department Records**: Merges incoming records from secondary departments; updates quantity for duplicate IDs and adds new IDs.
8. **Resource Analysis**: Displays total inventory count, Adequate/Low/Critical breakdown, list of items requiring immediate replenishment, and department-wise totals.
9. **Generate Report**: Formatted consolidated report suitable for administrative summary printing.
10. **Save Resources**: Exports inventory to `resources.txt`.
11. **Load Resources**: Imports inventory from `resources.txt` upon startup.

---

## 6. Data Structures Used

### Structure Definition (`struct Resource`)
```c
struct Resource {
    int id;               // Unique integer identifier (e.g. 101, 102)
    char name[50];        // Name of resource (e.g. "Paracetamol", "Ventilator")
    char type[30];        // Category (e.g. "Medicine", "Equipment", "Bed", "Supply")
    char department[30];  // Department (e.g. "Emergency", "ICU", "Surgery", "Pharmacy")
    int quantity;         // Available stock count
    int threshold;        // Minimum safe threshold limit
};
```

### Array of Structures
```c
struct Resource resources[MAX_RESOURCES]; // Fixed-size array storing up to 100 resources
int resourceCount = 0;                     // Tracks current number of active records
```

---

## 7. Algorithms & Pseudocode

### 7.1 Main Application Loop (Pseudocode)
```text
START
    Call loadResources() to read records from "resources.txt"

    REPEAT
        Display Main Menu Options (1 to 11)
        Read user choice

        SWITCH (choice)
            CASE 1: Call addResource()
            CASE 2: Call displayResources()
            CASE 3: Call updateResource()
            CASE 4: Call searchResource()
            CASE 5: Call sortResources()
            CASE 6: Call mergeResources()
            CASE 7: Call analyseResources()
            CASE 8: Call generateReport()
            CASE 9: Call saveResources()
            CASE 10: Call loadResources()
            CASE 11: Call saveResources(), Display Exit Message
            DEFAULT: Display "Invalid Option"
        END SWITCH
    UNTIL choice = 11
STOP
```

### 7.2 Recursive Search Algorithm (ID Search)
```text
FUNCTION recursiveSearchByID(arr, count, index, targetId):
    IF index >= count THEN
        RETURN -1  // Base Case 1: End of array reached, target not found
    END IF

    IF arr[index].id == targetId THEN
        RETURN index // Base Case 2: Target ID found at current index
    END IF

    // Recursive Step
    RETURN recursiveSearchByID(arr, count, index + 1, targetId)
END FUNCTION
```

### 7.3 Bubble Sort Algorithm
```text
FUNCTION sortResources(choice):
    FOR i = 0 TO resourceCount - 2 DO
        FOR j = 0 TO resourceCount - i - 2 DO
            Set shouldSwap = 0
            
            IF choice == 1 AND resources[j].id > resources[j+1].id THEN shouldSwap = 1
            IF choice == 2 AND strcmp(resources[j].name, resources[j+1].name) > 0 THEN shouldSwap = 1
            IF choice == 3 AND resources[j].quantity > resources[j+1].quantity THEN shouldSwap = 1
            IF choice == 4 AND status(resources[j]) > status(resources[j+1]) THEN shouldSwap = 1

            IF shouldSwap THEN
                Call swapResources(&resources[j], &resources[j+1]) // Pointer swap
            END IF
        END FOR
    END FOR
END FUNCTION
```

---

## 8. Sample Console Outputs (For Academic Screenshots)

### 8.1 Main Menu & Display Resources
```text
==================================================
   SMART EMERGENCY RESOURCE MANAGEMENT SYSTEM     
==================================================
 1. Add Resource
 2. Display Resources
 3. Update Resource
 4. Search Resource
 5. Sort Resources
 6. Merge Department Records
 7. Analyse Resources
 8. Generate Report
 9. Save Resources
10. Load Resources
11. Exit
==================================================
Enter your choice (1-11): 2

==================================================================================================
                                   CURRENT EMERGENCY RESOURCES                                    
==================================================================================================
ID     Name                   Type            Department      Qty      Threshold   Status    
--------------------------------------------------------------------------------------------------
101    Paracetamol            Medicine        Emergency       500      100         ADEQUATE  
102    Ventilator             Equipment       ICU             2        5           CRITICAL  
103    Emergency Bed          Bed             Emergency       4        5           LOW       
104    Oxygen Cylinder        Supply          ICU             20       10          ADEQUATE  
105    Surgical Gloves        Supply          Surgery         300      100         ADEQUATE  
106    Defibrillator          Equipment       ICU             1        4           CRITICAL  
107    IV Saline 500ml        Medicine        Emergency       40       100         CRITICAL  
108    N95 Masks              Supply          Pharmacy        150      50          ADEQUATE  
109    Morphine Injection     Medicine        Pharmacy        15       10          ADEQUATE  
110    Stretcher              Equipment       Emergency       3        8           CRITICAL  
==================================================================================================
Total Records Displayed: 10
```

### 8.2 Resource Analysis Output
```text
==================================================
               RESOURCE ANALYSIS                  
==================================================
Total Resource Types : 10
Total Quantity       : 1245 units

Adequate Resources   : 5
Low Resources        : 1
Critical Resources   : 4

--------------------------------------------------
Resources Requiring Immediate Replenishment:
--------------------------------------------------
102    - Ventilator             (CRITICAL  ) [Qty: 2, Threshold: 5]
103    - Emergency Bed          (LOW       ) [Qty: 4, Threshold: 5]
106    - Defibrillator          (CRITICAL  ) [Qty: 1, Threshold: 4]
107    - IV Saline 500ml        (CRITICAL  ) [Qty: 40, Threshold: 100]
110    - Stretcher              (CRITICAL  ) [Qty: 3, Threshold: 8]

--------------------------------------------------
DEPARTMENT-WISE AVAILABILITY:
--------------------------------------------------
Emergency       : 547 units
ICU             : 23 units
Surgery         : 300 units
Pharmacy        : 165 units
==================================================
```

---

## 9. Design Decisions, Challenges & Reflections

### Design Decisions
* **Single Source File (`main.c`)**: Chosen to ensure easy compilation in any IDE (Dev-C++, Code::Blocks, VS Code) without requiring complex Makefile or multi-file project configuration during viva defense.
* **Array of Structures**: Provides direct contiguous memory allocation and $O(1)$ indexing.
* **Pipe-Delimited File Format (`|`)**: Used instead of whitespace delimiters so resource names with spaces (e.g., `"Emergency Bed"`, `"Oxygen Cylinder"`) are read and parsed without corruption.

### Challenges Faced & Solutions
1. **Input Buffer Residual Newlines**: Mixing `scanf("%d")` with `fgets()` often leaves `\n` in the input buffer, causing subsequent string prompts to be skipped.
   - *Solution*: Built a dedicated `clearInputBuffer()` helper function called after every numeric `scanf`.
2. **Duplicate Resource ID Management**: Preventing duplicate IDs during both manual additions and department-wide record merging.
   - *Solution*: Utilized `recursiveSearchByID()` to inspect existing inventory before adding or updating records.

---

## 10. Viva Defense Questions & Answers Guide

**Q1: How does your program handle memory and resource structures?**
> *Answer*: The program defines a custom `struct Resource` containing fields for ID, Name, Type, Department, Quantity, and Threshold. A global array `resources[MAX_RESOURCES]` holds up to 100 resource records in contiguous memory.

**Q2: Where are pointers used in your project?**
> *Answer*: Pointers are used in two critical functions:
> 1. `updateResourceRecord(struct Resource *r)` receives a pointer to a specific resource structure and uses the arrow operator (`->`) to modify its fields directly in memory.
> 2. `swapResources(struct Resource *a, struct Resource *b)` receives pointers to two structures and swaps their values during Bubble Sorting.

**Q3: Where is recursion demonstrated?**
> *Answer*: Recursion is implemented in `recursiveSearchByID(struct Resource arr[], int count, int index, int targetId)`. It tests if `arr[index].id == targetId` (base case) and recursively calls `recursiveSearchByID(arr, count, index + 1, targetId)` until the item is found or the index exceeds bounds.

**Q4: How does status calculation work at boundary conditions?**
> *Answer*: The function `getStatus(quantity, threshold)` evaluates:
> - `quantity <= threshold / 2` $\rightarrow$ `CRITICAL`
> - `quantity <= threshold` $\rightarrow$ `LOW`
> - `else` $\rightarrow$ `ADEQUATE`

**Q5: How is file handling implemented?**
> *Answer*: Data is written using `fopen("resources.txt", "w")`, `fprintf()`, and `fclose()`. Data is read using `fopen("resources.txt", "r")`, `fgets()`, `sscanf()` with pipe delimiters, and `fclose()`.
