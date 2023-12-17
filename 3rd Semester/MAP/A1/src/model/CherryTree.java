package model;

public class CherryTree extends Tree{

    public CherryTree(int id, int age)
    {
        super(id, age);
    }

    @Override
    public String getTypeOfTree()
    {
        return "Cherry Tree";
    }

    @Override
    public String toString()
    {
        return "Cherry Tree with id " + this.id + " and age " + this.age;
    }
}
