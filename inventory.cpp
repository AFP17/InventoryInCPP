#include <iostream>
#include <map>
#include <string>
#include <iomanip> 

class InventoryManager {
private:
    std::map<std::string, long long> inventory; 
public:
    // Add or update items in the inventory
    void addItem(const std::string& item, long long quantity) {
        if (quantity <= 0 || quantity > 1000000) { // Limit to reasonable additions
            std::cout << "Invalid quantity. Please enter a value between 1 and 1,000,000.\n";
            return;
        }
        long long newQuantity = inventory[item] + quantity;
        if (newQuantity < inventory[item]) { 
            std::cout << "Quantity too large to add.\n";
            return;
        }
        inventory[item] = newQuantity;
        std::cout << "Added " << quantity << " units of " << item << ".\n";
    }

    // Remove items from the inventory
    bool removeItem(const std::string& item, long long quantity) {
        if (quantity <= 0 || quantity > 1000000) { // Limit to reasonable removals
            std::cout << "Invalid quantity. Please enter a value between 1 and 1,000,000.\n";
            return false;
        }
        if (inventory.find(item) != inventory.end() && inventory[item] >= quantity) {
            inventory[item] -= quantity;
            if (inventory[item] == 0) {
                inventory.erase(item);
            }
            std::cout << "Removed " << quantity << " units of " << item << ".\n";
            return true;
        }
        std::cout << "Failed to remove " << quantity << " units of " << item << " (not enough stock or item not found).\n";
        return false;
    }

    // Display all items in the inventory
    void displayInventory() const {
        if (inventory.empty()) {
            std::cout << "Inventory is empty.\n";
        } else {
            std::cout << "Inventory:\n";
            for (const auto& item : inventory) {
                std::cout << std::setw(20) << std::left << item.first << ": "
                          << std::setw(10) << std::right << item.second << " units\n";
            }
        }
    }
};

int main() {
    InventoryManager manager;
    bool running = true;

    while (running) {
        std::cout << "1. Add Item\n2. Remove Item\n3. Display Inventory\n4. Exit\nEnter your choice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        std::string item;
        long long quantity;

        switch (choice) {
            case 1:
                std::cout << "Enter item name and quantity to add (e.g., Apples 10): ";
                std::cin >> item >> quantity;
                manager.addItem(item, quantity);
                break;
            case 2:
                std::cout << "Enter item name and quantity to remove (e.g., Apples 5): ";
                std::cin >> item >> quantity;
                manager.removeItem(item, quantity);
                break;
            case 3:
                manager.displayInventory();
                break;
            case 4:
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
        std::cout << "\n"; 
    }

    return 0;
}
