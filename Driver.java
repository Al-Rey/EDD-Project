package test;

import java.util.Scanner;

public class Driver {
	public static void main(String[] args) {
		String answer = "";
		Scanner scan = new Scanner(System.in);
		
		main:
		while (true) {
			answer = scan.next();//asks you to input a number
			
			//pressing the number one places you in the order, pressing them again signifies the cancel button
			switch (answer) {
			case "1"://represent student 1
				Order.reorder(1);
				break;
			case "2"://represent student 2
				Order.reorder(2);
				break;
			case "3"://represent student 3
				Order.reorder(3);
				break;
			case "4"://represent student 4
				Order.reorder(4);
				break;
			case "5"://represent student 5
				Order.reorder(5);
				break;
			case "6"://represent student 6
				Order.reorder(6);
				break;
			default://ends the program
				break main;
			}

			Order.printArray();//prints the entire array
		}

	}

}
