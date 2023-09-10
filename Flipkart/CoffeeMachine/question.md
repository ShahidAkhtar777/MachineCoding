**Coffee Machine Simulation**

You are required to create a functional coffee machine simulation that manages ingredient stocking, beverage preparation, and stock tracking. The coffee machine should handle various beverages and display relevant messages for ingredient stocking, beverage preparation success, and any ingredient shortages. Each beverage requires specific ingredients, which can be shared across multiple beverages. Initial ingredient stock quantities and the required ingredients for each beverage will be provided.

**Requirements:**

1. Implement the following features in your coffee machine simulation:

   - Stock ingredients with their initial quantities.
   - Prepare beverages by deducting the required ingredients from the stock.
   - Display the current quantity of each ingredient in stock.
   - Handle errors by displaying appropriate messages when ingredients are unavailable for beverage preparation.

2. Ingredients available for stocking:

   - hot_water
   - hot_milk
   - coffee_decoction
   - sugar_syrup
   - tea_leaves_syrup
   - green_tea_syrup

3. Beverages that can be prepared:

   - hot_tea: Requires hot_water (200), hot_milk (100), sugar_syrup (30), tea_leaves_syrup (30)
   - hot_coffee: Requires hot_water (100), hot_milk (400), coffee_decoction (50), sugar_syrup (30)
   - black_tea: Requires hot_water (300), sugar_syrup (20), tea_leaves_syrup (30)
   - green_tea: Requires hot_water (200), sugar_syrup (20), green_tea_syrup (30)

4. You need to design a clean and modular API with proper error handling and usage of object-oriented concepts.

5. Ensure that your code is functional, readable, and well-documented.

6. Implement extensibility so that the code can accommodate new requirements with minimal changes.

**Bonus (Optional):**

- Write functional test cases for your simulation library.
- Add functionality to enable/disable specific beverages temporarily.

**Sample Test Case:**

```python
add_stock("hot_water", 100)
add_stock("sugar_syrup", 200)
get_stock()
prepare("black_tea")
prepare("hot_coffee")
get_stock()
prepare("green_tea")
get_stock()
```

**Expectations:**

- Provide a clear and concise problem statement that covers all the requirements and features of the coffee machine simulation.
- Ensure that the problem statement is well-structured and easy to understand.
- Include the necessary instructions for implementing the coffee machine simulation, handling ingredients, preparing beverages, and displaying stock information and messages.
- Make sure the provided code or solution demonstrates the functionality as described in the problem statement.

**Note:** You can use the provided information to create a detailed problem statement in a file named "question.md".