import java.util.*;
import java.io.*;

/**
 * A menu-driven Telephone Book program that allows the user to:
 * 1. Insert a new directory [Name & Telephone Number]
 * 2. Retrieve a directory
 * 3. Delete a directory
 * 4. Display the directory
 *
 * Uses the LinkedList, PersonNode, and Telephone Book classes for support.
 *
 * @assignment ICS 211 [FINAL PROJECT]
 * @author Gabriel Viloria
 * @date December 4, 2015
 */
class ViloriaGabrielProject {

    /**
     * Runs the program
     *
     * @param args The input file as the first argument and output file as the second.
     */
    public static void main(String[] args) {

        // Check if there are exactly 2 arguments
        if (args.length != 2) {
            System.out.println("This program takes in two command-line arguments:" + "\n" +
                    "[Input File] [Output File]" + "\n\n" +
                    "With the given files, it should look like: " + "\n" +
                    "C:\\Users\\Gabe\\Desktop\\input-project.csv" + " " + "C:\\Users\\Gabe\\Desktop\\input-project.csv");
            System.exit(1);
        }

        // Instantiates a TelephoneBook object
        TelephoneBook book = new TelephoneBook();

        // Reads the input file
        readFromFile(book, args[0]);

        // Displays and Runs the Menu and Choices
        runTelephone(book);

        // Writes to the output file
        writeToFile(book, args[1]);

    }

    /**
     * Runs the Telephone Book
     *
     * @param book TelephoneBook object to add names and telephone numbers to
     */
    public static void runTelephone(TelephoneBook book) {

        // Message to user
        System.out.println("**********************************");
        System.out.println("Personal Telephone Book Hash Table");
        System.out.println("**********************************");
        System.out.println();


        try {

        // Scanner to read in from keyboard
        Scanner sc = new Scanner(System.in);

        // Displays the menu and retrieve the user's choice
        displayMenu();

        int choice = getChoice();
        System.out.println();

            // Continues to loop until the user exits
            while (choice != 5) {

                // [Insert] Prompts user for name and telephone number.
                if (choice == 1) {
                    String name, telephone;
                    System.out.print("Enter person's name: ");
                    name = sc.nextLine();
                    System.out.print("Enter person's telephone number: ");
                    telephone = sc.nextLine();
                    book.insert(name, telephone);

                // [Retrieve] Retrieves the number of the name the user inputs. It is case-sensitive.
                } else if (choice == 2) {
                    String name;
                    System.out.print("Enter person's name: ");
                    name = sc.nextLine();
                    System.out.println("The telephone number is: " + book.retrieve(name).getTelephoneNumber());

                // [Delete] Deletes the number of the name the user inputs. It is case-sensitive.
                } else if (choice == 3) {
                    String name;
                    System.out.print("Enter person's name: ");
                    name = sc.nextLine();
                    System.out.println("Deleting: " + book.retrieve(name));
                    book.delete(name);

                // [Display] Displays the contents of the telephone book.
                } else if (choice == 4) {
                    System.out.println(book);
                }

                // Re-displays the menu and prompts the user for a choice again
                System.out.println();
                displayMenu();
                choice = getChoice();
                System.out.println();
            }

            //Catches exceptions
        } catch (Exception e) {

            System.out.println("An error has occurred: " + e + "\n\n" + "Names are case-sensitive.");
        }
    }

    /**
     * Gets the user's choice.
     *
     * @return Number that the user picked.
     */
    public static int getChoice() {

        Scanner sc = new Scanner(System.in);
        int choice = -1;

        // Continually prompts user while choice value is invalid
        while (choice < 1 || choice > 5) {
            System.out.print("Enter choice (1-5): ");

            try {
                // Attempts to parse the input as an integer
                choice = Integer.parseInt(sc.nextLine());

            } catch (Exception e) {
                System.out.println("Error: " + e);
            }

            // If the given integer is still out of range, prompts user with message again.
            if (choice < 1 || choice > 5)
            System.out.print("Integer must be between 1-5." + "\n");
        }
        return choice;
    }

    /**
     * Reads the names and telephone numbers from the input file
     *
     * @param book TelephoneBook object to add names and telephone numbers to
     * @param inputFile File to read
     */
    public static void readFromFile(TelephoneBook book, String inputFile) {

        System.out.println("Reading from input file: " + inputFile);
        System.out.println();

        try {
            // Attempts to open the specified file
            Scanner sc = new Scanner(new File(inputFile));

            // Skips the first line of the input file
            sc.nextLine();

            // Keeps reading from the file until it has gone through all
            while (sc.hasNextLine()) {

                // Parse the data we read in
                String data[] = sc.nextLine().split(",");
                book.insert(data[0], data[1]);
            }

            // Catches exceptions
        } catch (FileNotFoundException e) {

            // Quit the program if we couldn't find the file
            System.out.println("Could not read " + inputFile);
            System.exit(1);
        }
    }

    /**
     * Writes the names and telephone numbers to the output file
     *
     * @param book TelephoneBook object to write to file
     * @param outputFile File to write to
     */
    public static void writeToFile(TelephoneBook book, String outputFile) {

        try {
            // Attempt to open the specified file
            PrintWriter out = new PrintWriter(new FileOutputStream(new File(outputFile)), false);

            // Output the dummy line
            out.println("name,telephone");
            out.print(book.toPrintString());

            // Close the file stream
            out.close();
            System.out.println("Wrote to output file: " + outputFile);

            // Catches exceptions
        } catch (IOException e) {
            // If there was an error writing to the file
            System.out.println("Could not write to " + outputFile);
            System.exit(1);
        }
    }

    /**
     * Displays the menu to the user.
     */
    public static void displayMenu() {
        System.out.println("[MAIN MENU]");
        System.out.println("1. Insert telephone number");
        System.out.println("2. Retrieve telephone number");
        System.out.println("3. Delete telephone number");
        System.out.println("4. Display telephone book");
        System.out.println("5. End program");
    }
}

/**
 * Class to store person's name, telephone number, and reference
 * to next node.
 */
class PersonNode {

    // [Data Fields]

    // Person's name
    private String name;

    // Person's telephone number
    private String telephoneNumber;

    // Reference to next person
    private PersonNode next;

    /**
     * Constructor to initialize name, telephone number, and next reference.
     *
     * @param name Person's name
     * @param telephoneNumber Person's telephone number
     */
    public PersonNode(String name, String telephoneNumber) {
        this.name = name;
        this.telephoneNumber = telephoneNumber;
        next = null;
    }

    /**
     * Return PersonNode in the form of a string
     *
     * @return String representation of PersonNode
     */
    public String toString() {
        return name + " " + telephoneNumber;
    }

    /**
     * Retrieve name of person
     *
     * @return Name of person
     */
    public String getName() {
        return name;
    }

    /**
     * Retrieve telephone number of person
     *
     * @return Telephone number of person
     */
    public String getTelephoneNumber() {
        return telephoneNumber;
    }

    /**
     * Retrieve next reference to person
     *
     * @return Reference to the next PersonNode object
     */
    public PersonNode getNext() {
        return next;
    }

    /**
     * Set the next person reference
     * @param person Next person to point to
     */
    public void setNext(PersonNode person) {
        next = person;
    }
}

/**
 * This class is an implementation of a basic LinkedList
 * to add, retrieve, and remove PersonNode objects.
 */
class LinkedList {

    // Reference to head of LinkedList
    private PersonNode head;

    /**
     * Constructor for linked list.
     *
     * Set head reference to null.
     */
    public LinkedList() {
        head = null;
    }

    /**
     * Return LinkedList in a string in printable form.
     *
     * @return string representation of the LinkedList.
     */
    public String toString() {

        // String to return
        String line = "";

        // Variable to loop through our linkedlist
        PersonNode check = head;

        // Continue looping as long as we have not hit the end
        while (check != null) {
            line += check + " => ";
            // Move forward
            check = check.getNext();
        }
        // Add null at the end to the string
        line += "null";
        return line;
    }

    /**
     * Converts LinkedList to String form to print to a file.
     *
     * @return String representation of Linkedlist to print to file.
     */
    public String toPrintString() {
        String line = "";
        // Variable to loop through linked list
        PersonNode check = head;
        // Keep looping until we hit the end
        while (check != null) {
            // Add name and telephone number separated by a comma
            line += check.getName() + "," + check.getTelephoneNumber();
            if (check.getNext() != null) {
                // If there are more elements, add a new line
                line += "\n";
            }
            // Move through the list
            check = check.getNext();
        }
        return line;
    }

    /**
     * Adds a new PersonNode to our linked list and
     * adds a new person to the front of list.
     *
     * @param person PersonNode to add
     */
    public void add(PersonNode person) {
        person.setNext(head);
        head = person;
    }

    /**
     * Retrieves the PersonNode object of the given name.
     *
     * @param name PersonNode to find
     * @return PersonNode with the given name specified
     */
    public PersonNode get(String name) {

        // PersonNode object to return
        PersonNode ret = null;

        // Variable to loop through linked list
        PersonNode check = head;
        while (check != null) {
            // Check if we found the person
            if (check.getName().equals(name)) {
                ret = check;
                break;
            }
            // Move through the list
            check = check.getNext();
        }

        // Return person
        return ret;
    }

    /**
     * Removes the PersonNode object of the specified name.
     *
     * @param name PersonNode to find and remove
     */
    public void remove(String name) {

        // Check if the head is the node we want to remove
        if (head.getName().equals(name)) {
            head = head.getNext();

        } else {

            // Variable to loop through linked list
            PersonNode check = head;

            while (check.getNext() != null) {

                // Check if we found the PersonNode
                if (check.getNext().getName().equals(name)) {

                    // Remove the person by rearranging the pointer
                    check.setNext(check.getNext().getNext());
                    break;
                }
                // Move through the list
                check = check.getNext();
            }
        }
    }
}

/**
 * Stores the array of LinkedLists for hash insertion, retrieval, and deletion.
 */
class TelephoneBook {

    // Array of LinkedLists
    private LinkedList[] people;

    /**
     * Instantiate array of LinkedList and initialize each
     * LinkedList object in the array.
     */
    public TelephoneBook() {
        people = new LinkedList[7];
        for (int i = 0; i < 7; i++) {
            people[i] = new LinkedList();
        }
    }

    /**
     * Insert a new PersonNode object with the given name and telephone number.
     *
     * @param name Name of person to add
     * @param telephone Telephone of person to add
     */
    public void insert(String name, String telephone) {
        // Mod by 7 because of [LinkedList's Array Size]
        people[name.hashCode() % 7].add(new PersonNode(name, telephone));
    }

    /**
     * Retrieve a PersonNode object with the given name
     *
     * @param name Name of person to retrieve
     */
    public PersonNode retrieve(String name) {
        return people[name.hashCode() % 7].get(name);
    }

    /**
     * Delete a PersonNode object with the given name
     *
     * @param name Name of the person to delete
     */
    public void delete(String name) {
        people[name.hashCode() % 7].remove(name);
    }

    /**
     * Convert LinkedList to printable form
     *
     * @return Printable form of LinkedList
     */
    public String toString() {

        String line = "";
        // Loop through the LinkedList and converts to string
        for (int i = 0; i < people.length; i++) {
            line += "table[" + i + "]" + " => " + people[i] + "\n";
        }
        return line;
    }

    /**
     * Converts array of LinkedList to String form to print to a file.
     *
     * @return String representation of array of the LinkedList to print to file.
     */
    public String toPrintString() {

        String line = "";
        // Loop through our array
        for (int i = 0; i < people.length; i++) {

            // String to possibly add
            String toAdd = people[i].toPrintString().trim();

            // If there are no PersonNode elements in the array, it returns an empty String
            // Check that we don't have an empty string
            if (!toAdd.isEmpty()) {

                // Add the information to our return string
                line += people[i].toPrintString();

                // Add a new line at the end, we can always trim it off later with the .trim() method
                if (i < people.length - 1) {
                    line += "\n";
                }
            }
        }
        return line;
    }
}
