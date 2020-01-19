package com.company;

import java.util.Scanner;

public class Car {
    private String name;
    private String model;
    private String color;
    private int weight;
    private int maxspeed;
    private int year;

    public Car(){
        System.out.println("constructor without param");
        name = "Unknown";
        model = "Unknown";
        color = "Unknown";
        weight = 0;
        maxspeed = 0;
        year = 1767;
    }
    public Car(String newname, String newmodel, String newcolor, int newweight, int newmaxspeed, int newyear){
        System.out.println("constructor with param");
        name = newname;
        model = newmodel;
        color = newcolor;
        weight = newweight;
        maxspeed = newmaxspeed;
        year = newyear;
    }
    public void getCar(){
        System.out.printf("NAME: %s\n", name);
        System.out.printf("MODEL: %s\n", model);
        System.out.printf("COLOR: %s\n", color);
        System.out.printf("WEIGHT: %s\n", weight);
        System.out.printf("MAXSPEED: %s\n", maxspeed);
        System.out.printf("YEAR: %s\n", year);
    }
    public void setCar(){
        Scanner in = new Scanner(System.in);
        System.out.println("ENTER >>");
        System.out.print("NAME: ");
        name = in.nextLine();
        System.out.print("MODEL: ");
        model = in.nextLine();
        System.out.print("COLOR: ");
        color = in.nextLine();
        System.out.print("WEIGHT: ");
        weight = in.nextInt();
        System.out.print("MAXSPEED: ");
        maxspeed = in.nextInt();
        System.out.print("YEAR: ");
        year = in.nextInt();
        in.close();
    }
}
