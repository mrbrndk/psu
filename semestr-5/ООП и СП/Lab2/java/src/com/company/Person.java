package com.company;

public class Person {
    private String name;
    public static Person first;
    public static Person last;
    public Person next;
    public Person()
    {
        next = null;
        if(first == null) first = this;
        if(last != null) last.next = this;
        last = this;

        name = "Vladimir";
    }
    public static void print()
    {
        Person i = first;
        while(i != null)
        {
            i.show();
            i = i.next;
        }
    }
    public void show()
    {
        System.out.printf("Name: %s\n", name);
    }
}
