package view;

import controller.Controller;
import model.AppleTree;
import model.CherryTree;
import model.PearTree;
import model.Tree;

import java.util.Scanner;

public class View {
    private Controller controller;
    Scanner scanner;

    public View(Controller controller) {
        this.controller = controller;
        this.scanner = new Scanner(System.in);
    }

    public void printMenu() {
        System.out.println("0. Exit");
        System.out.println("1. Add tree");
        System.out.println("2. Remove tree");
        System.out.println("3. Print all trees");
        System.out.println("4. Print all trees with age older than age");
    }

    public void handleAdd() {
        System.out.println("Enter id: ");
        int id = Integer.parseInt(scanner.nextLine());
        System.out.println("Enter age: ");
        int age = Integer.parseInt(scanner.nextLine());
        System.out.println("Enter type (apple, pear, cherry): ");
        String type = scanner.nextLine();

        switch (type) {
            case "apple":
                try {
                    this.controller.addTree(new AppleTree(id, age));
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                }
                break;
            case "pear":
                try {
                    this.controller.addTree(new PearTree(id, age));
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                }
                break;
            case "cherry":
                try {
                    this.controller.addTree(new CherryTree(id, age));
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                }
                break;
            default:
                System.out.println("Invalid type. Try again");
        }
    }

    public void handleRemove() {
        this.handlePrintAll();
        System.out.println("Enter id: ");
        int id = Integer.parseInt(scanner.nextLine());
        try {
            this.controller.removeTree(id);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void handlePrintAll() {
        Tree trees[] = this.controller.getTrees();
        if (trees.length == 0) {
            System.out.println("No trees yet. Add some");
            return;
        }
        for (int i = 0; i < trees.length; i++) {
            if (trees[i] == null) {
                break;
            }
            System.out.println(trees[i]);
        }
    }

    public void handlePrintAllOlderThan() {
        System.out.println("Enter age: ");
        int age = Integer.parseInt(scanner.nextLine());
        Tree[] trees = this.controller.getAllTreesWithAgeOlderThanValue(age);
        if (trees.length == 0) {
            System.out.println("No trees older than " + age);
            return;
        }
        for (model.Tree tree : this.controller.getAllTreesWithAgeOlderThanValue(age)) {
            if (tree == null) {
                break;
            }
            System.out.println(tree);
        }
    }

    public void run() {
        while (true) {
            this.printMenu();
            System.out.println("Enter option: ");
            int option = Integer.parseInt(scanner.nextLine());
            switch (option) {
                case 0:
                    System.out.println("goodbye!");
                    return;
                case 1:
                    this.handleAdd();
                    break;
                case 2:
                    this.handleRemove();
                    break;
                case 3:
                    this.handlePrintAll();
                    break;
                case 4:
                    this.handlePrintAllOlderThan();
                    break;
                default:
                    System.out.println("Invalid option");
            }
        }
    }
}
