package test;

public abstract class Order {
	static int[] order = { 0, 0, 0, 0, 0, 0 };
	static int index, max, oldpLace;
	static boolean allZero;

	public static void reorder(int studentNum) {
		index = studentNum - 1;// changes the student number to it's assigned index
		max = 0;// resets the max number to zero

		// when you press the button once
		if (order[index] == 0) {
			// loops through the array and finds the highest value
			for (int x : order) {
				if (max < x) {
					max = x;
				}
			}
			/*
			 * set the current value of the index to one more of the existing
			 * highest value in the array.
			 */
			order[index] = ++max;

		} else {// when you press the button a second time
			/*
			 * iterates through the array moves the items below the desired one
			 * in the order list up one
			 */
			for (int x = 0; x < order.length; x++) {
				if (order[x] > order[index]) {
					order[x]--;
				}
			}
			// resets the desired element to zero (not in the order)
			order[index] = 0;
		}
	}

	// prints the order list
	public static void printArray() {
		for (int x : order) {
			System.out.print(x + " ");
		}
		System.out.println("\n");
	}
}
