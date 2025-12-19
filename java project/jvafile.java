import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
import java.text.SimpleDateFormat;
import java.util.*;
import javax.swing.JOptionPane;

/*
 MallManagementApplet.java
 Single-file integrated Mall Management System (Applet + runnable Frame)
 - 3 Shops (Electronics, Fashion, Food Court) each with products
 - Billing (₹ only), Parking (10 slots each), Lift & Navigation
 - Run as: javac MallManagementApplet.java
          java MallManagementApplet
*/

public class MallManagementApplet extends Applet implements ActionListener {
    // UI
    private TextArea output;
    private Panel topPanel;
    private Button btnShops, btnBilling, btnParking, btnLift, btnSaveExit;

    // Data
    private List<Shop> shops = new ArrayList<>();
    private List<Product> products = new ArrayList<>(); // all products catalog
    private BillingSystem billing = new BillingSystem();
    private Parking parking = new Parking();
    private Navigation navigation = new Navigation();

    @Override
    public void init() {
        setLayout(new BorderLayout());
        topPanel = new Panel(new FlowLayout(FlowLayout.CENTER, 8, 8));
        btnShops = new Button("Shops");
        btnBilling = new Button("Billing");
        btnParking = new Button("Parking");
        btnLift = new Button("Lift");
        btnSaveExit = new Button("Save & Exit");

        btnShops.addActionListener(this);
        btnBilling.addActionListener(this);
        btnParking.addActionListener(this);
        btnLift.addActionListener(this);
        btnSaveExit.addActionListener(this);

        topPanel.add(btnShops);
        topPanel.add(btnBilling);
        topPanel.add(btnParking);
        topPanel.add(btnLift);
        topPanel.add(btnSaveExit);

        output = new TextArea(25, 100);
        output.setFont(new Font("Monospaced", Font.PLAIN, 12));
        add(topPanel, BorderLayout.NORTH);
        add(output, BorderLayout.CENTER);

        // Populate shops & products (3 shops as requested)
        populateSampleData();

        println("Mall Management System initialized. Click buttons above to interact.");
        println("Shops loaded: " + shops.size() + "  |  Products: " + products.size());
    }

    // Action handling
    public void actionPerformed(ActionEvent e) {
        Object src = e.getSource();
        if (src == btnShops) {
            showShopsUI();
        } else if (src == btnBilling) {
            billing.selectItemsUI(this, output, products);
        } else if (src == btnParking) {
            parking.showParkingUI(this, output);
        } else if (src == btnLift) {
            Lift lift = new Lift(this, output, navigation, billing);
            lift.showLiftUI();
        } else if (src == btnSaveExit) {
            saveData();
            println("Data saved (shops.txt / products.txt). Closing.");
            // Close window if running as frame
            Frame f = getFrameAncestor();
            if (f != null) f.dispose();
        }
    }

    private Frame getFrameAncestor() {
        Container c = this.getParent();
        while (c != null && !(c instanceof Frame)) c = c.getParent();
        return (Frame) c;
    }

    private void println(String s) { output.append(s + "\n"); }

    private void populateSampleData() {
        // Shop 1: Electronics
        Shop elec = new Shop("Electronics Hub", 1, "TVs, Laptops, Phones", "10AM-9PM");
        elec.items.add("TV - ₹30000");
        elec.items.add("Laptop - ₹45000");
        elec.items.add("Earbuds - ₹1500");

        // Shop 2: Fashion
        Shop fash = new Shop("Fashion Store", 2, "Clothes & Accessories", "10AM-9PM");
        fash.items.add("Jeans - ₹1200");
        fash.items.add("Shirt - ₹700");
        fash.items.add("Jacket - ₹2500");

        // Shop 3: Food Court
        Shop food = new Shop("Food Court", 3, "Fast Food & Beverages", "10AM-11PM");
        food.items.add("Burger - ₹150");
        food.items.add("Pizza Slice - ₹200");
        food.items.add("Coffee - ₹120");

        shops.add(elec);
        shops.add(fash);
        shops.add(food);

        // Flatten products (assign product IDs)
        products.clear();
        int id = 1;
        for (Shop s : shops) {
            for (String it : s.items) {
                // Parse name and price "Name - ₹price"
                String[] parts = it.split(" - ₹");
                String pname = parts[0].trim();
                double price = 0;
                try { price = Double.parseDouble(parts[1].trim()); } catch (Exception ex) { price = 0; }
                products.add(new Product(String.format("P%03d", id++), pname, s.name, price));
            }
        }
    }

    private void showShopsUI() {
        StringBuilder sb = new StringBuilder();
        sb.append("=== Shops Directory ===\n");
        for (int i = 0; i < shops.size(); i++) {
            Shop s = shops.get(i);
            sb.append((i+1) + ". " + s.name + " (Floor " + s.floor + ") - " + s.timing + "\n");
            for (String it : s.items) sb.append("    - " + it + "\n");
        }
        output.append(sb.toString());
        String sel = JOptionPane.showInputDialog("Enter shop number to view (or blank to cancel):");
        if (sel == null || sel.trim().isEmpty()) return;
        try {
            int idx = Integer.parseInt(sel.trim()) - 1;
            if (idx >= 0 && idx < shops.size()) {
                Shop s = shops.get(idx);
                output.append("\n--- " + s.name + " Details ---\n");
                output.append("Floor: " + s.floor + "\n");
                output.append("Timing: " + s.timing + "\n");
                output.append("Products:\n");
                int count = 1;
                for (Product p : products) if (p.shopName.equals(s.name)) {
                    output.append("  " + count++ + ". " + p.name + " - ₹" + p.price + " (ID: " + p.id + ")\n");
                }
                output.append("\n");
            }
        } catch (Exception ex) { /* ignore invalid */ }
    }

    private void saveData() {
        try (java.io.PrintWriter pw = new java.io.PrintWriter("shops.txt")) {
            for (Shop s : shops) pw.println(s.name + "|" + s.floor + "|" + s.description + "|" + s.timing);
        } catch (Exception ex) { println("Error saving shops: " + ex.getMessage()); }
        try (java.io.PrintWriter pw = new java.io.PrintWriter("products.txt")) {
            for (Product p : products) pw.println(p.id + "|" + p.name + "|" + p.shopName + "|" + p.price);
        } catch (Exception ex) { println("Error saving products: " + ex.getMessage()); }
    }

    // ---------------- Domain classes ----------------
    static class Shop {
        String name;
        int floor;
        String description;
        String timing;
        List<String> items = new ArrayList<>();
        Shop(String n, int f, String d, String t) { name = n; floor = f; description = d; timing = t; }
    }

    static class Product {
        String id;
        String name;
        String shopName;
        double price;
        Product(String id, String name, String shopName, double price) { this.id = id; this.name = name; this.shopName = shopName; this.price = price; }
    }

    // ---------------- Parking ----------------
    static class Parking {
        int twoWheelerSlots = 10;
        int fourWheelerSlots = 10;

        void showParkingUI(Applet app, TextArea out) {
            String status = getStatus();
            String[] options = {"Park 2W", "Exit 2W", "Park 4W", "Exit 4W", "Reset", "Close"};
            while (true) {
                String choice = (String) JOptionPane.showInputDialog(null, "Parking Status: " + status + "\nChoose action:", "Parking", JOptionPane.PLAIN_MESSAGE, null, options, options[0]);
                if (choice == null || choice.equals("Close")) break;
                if (choice.equals("Park 2W")) {
                    if (twoWheelerSlots > 0) twoWheelerSlots--; else JOptionPane.showMessageDialog(null, "No 2-wheeler slots available!");
                } else if (choice.equals("Exit 2W")) {
                    if (twoWheelerSlots < 10) twoWheelerSlots++;
                } else if (choice.equals("Park 4W")) {
                    if (fourWheelerSlots > 0) fourWheelerSlots--; else JOptionPane.showMessageDialog(null, "No 4-wheeler slots available!");
                } else if (choice.equals("Exit 4W")) {
                    if (fourWheelerSlots < 10) fourWheelerSlots++;
                } else if (choice.equals("Reset")) {
                    twoWheelerSlots = 10; fourWheelerSlots = 10;
                }
                status = getStatus();
                out.append("Parking -> " + status + "\n");
            }
        }

        private String getStatus() { return "2W: " + twoWheelerSlots + "/10   |   4W: " + fourWheelerSlots + "/10"; }
    }

    // ---------------- Navigation ----------------
    static class Navigation {
        // simple floor info mapping
        String getFloorInfo(int floor) {
            switch (floor) {
                case 0: return "Ground: Entrance & Parking";
                case 1: return "1st Floor: Electronics & Fashion";
                case 2: return "2nd Floor: Fashion & Food Court";
                case 3: return "3rd Floor: Cinema & Entertainment";
                case 4: return "4th Floor: Rooftop & Services";
                default: return "Unknown";
            }
        }
    }

    // ---------------- BillingSystem ----------------
    static class BillingSystem {
        Map<String, Double> cart = new LinkedHashMap<>();
        String customerName = "";
        String paymentMode = "";
        String cardNumber = "", cvv = "", upi = "";

        void selectItemsUI(Applet app, TextArea out, List<Product> products) {
            // show product list and allow adding by ID
            StringBuilder sb = new StringBuilder();
            sb.append("Available Products:\n");
            for (Product p : products) sb.append(p.id + " | " + p.name + " (" + p.shopName + ") - ₹" + p.price + "\n");
            out.append(sb.toString());

            while (true) {
                String pid = JOptionPane.showInputDialog("Enter Product ID to add to cart (or blank/Cancel to finish):");
                if (pid == null || pid.trim().isEmpty()) break;
                Product found = null;
                for (Product p : products) if (p.id.equalsIgnoreCase(pid.trim())) { found = p; break; }
                if (found == null) { JOptionPane.showMessageDialog(null, "Product ID not found."); continue; }
                String qtys = JOptionPane.showInputDialog("Enter quantity for " + found.name + ":");
                int qty = 1;
                try { qty = Integer.parseInt(qtys.trim()); if (qty < 1) qty = 1; } catch (Exception ex) { qty = 1; }
                double added = found.price * qty;
                cart.put(found.name + " x" + qty, cart.getOrDefault(found.name + " x" + qty, 0.0) + added);
                out.append("Added: " + found.name + " x" + qty + " -> ₹" + added + "\n");
            }

            if (cart.isEmpty()) { JOptionPane.showMessageDialog(null, "No items in cart."); return; }
            collectCustomerDetails();
            generateBill(out);
        }

        void collectCustomerDetails() {
            customerName = JOptionPane.showInputDialog("Enter customer name:");
            if (customerName == null) customerName = "";
            paymentMode = JOptionPane.showInputDialog("Payment Mode (Card/Cash/UPI):");
            if (paymentMode == null) paymentMode = "Cash";
            if (paymentMode.equalsIgnoreCase("Card")) {
                cardNumber = JOptionPane.showInputDialog("Credit Card Number:");
                cvv = JOptionPane.showInputDialog("CVV:");
            } else if (paymentMode.equalsIgnoreCase("UPI")) {
                upi = JOptionPane.showInputDialog("Enter your UPI ID:");
            }
        }

        void generateBill(TextArea out) {
            out.append("\n========== FINAL BILL ==========\n");
            out.append("Customer: " + (customerName.isEmpty() ? "Guest" : customerName) + "\n");
            out.append("Payment Mode: " + paymentMode + "\n");
            if (paymentMode.equalsIgnoreCase("Card")) out.append("Card No: " + cardNumber + "\n");
            if (paymentMode.equalsIgnoreCase("UPI")) out.append("UPI ID: " + upi + "\n");
            out.append("Date: " + new SimpleDateFormat("yyyy-MM-dd").format(new Date()) + "\n");
            out.append("Time: " + new SimpleDateFormat("HH:mm").format(new Date()) + "\n\n");
            double total = 0;
            out.append("Items:\n");
            for (Map.Entry<String, Double> e : cart.entrySet()) {
                out.append(" - " + e.getKey() + " : ₹" + e.getValue() + "\n");
                total += e.getValue();
            }
            out.append("\nTotal Amount: ₹" + String.format("%.2f", total) + "\n");
            out.append("================================\n\n");
            JOptionPane.showMessageDialog(null, "Payment Successful! Total ₹" + String.format("%.2f", total));
            cart.clear();
        }
    }

    // ---------------- Lift ----------------
    static class Lift {
        Applet app;
        TextArea out;
        Navigation nav;
        BillingSystem bill;
        Lift(Applet app, TextArea out, Navigation nav, BillingSystem bill) { this.app = app; this.out = out; this.nav = nav; this.bill = bill; }

        void showLiftUI() {
            String[] floors = {"0 - Ground", "1 - First", "2 - Second", "3 - Third", "4 - Fourth"};
            String choice = (String) JOptionPane.showInputDialog(null, "Choose Floor", "Lift", JOptionPane.PLAIN_MESSAGE, null, floors, floors[0]);
            if (choice == null) return;
            int floor = Integer.parseInt(choice.split(" - ")[0].trim());
            out.append("\nYou moved to floor: " + floor + " -> " + nav.getFloorInfo(floor) + "\n");
            String act = JOptionPane.showInputDialog("Enter 1 to View Shops on this floor, 2 for Billing, blank to close:");
            if (act == null || act.trim().isEmpty()) return;
            if (act.trim().equals("1")) { // show shops on that floor
                // in this simplified integration we just print shops that match floor
                out.append("--- Shops on Floor " + floor + " ---\n");
                for (Shop s : ((MallManagementApplet)app).shops) {
                    if (s.floor == floor) {
                        out.append(" * " + s.name + " : " + s.description + " (" + s.timing + ")\n");
                    }
                }
            } else if (act.trim().equals("2")) {
                bill.selectItemsUI(app, out, ((MallManagementApplet)app).products);
            }
        }
    }

    // ---------------- Main wrapper so applet can run as a desktop app ----------------
    public static void main(String[] args) {
        /*
         Helpful notes:
         - This program is an Applet-based UI embedded in a Frame so it runs in modern JDKs.
         - Compile: javac MallManagementApplet.java
         - Run:     java MallManagementApplet
         - The top buttons: Shops, Billing, Parking, Lift, Save & Exit
         - Billing works by entering product IDs (e.g., P001) and quantities.
         - Parking manages 10 slots each for 2-wheeler and 4-wheeler.
        */
        Frame frame = new Frame("Mall Management System - Applet Mode");
        MallManagementApplet app = new MallManagementApplet();
        app.init();
        frame.add(app);
        frame.setSize(950, 650);
        frame.addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent e) { System.exit(0); }
        });
        frame.setVisible(true);
    }
}