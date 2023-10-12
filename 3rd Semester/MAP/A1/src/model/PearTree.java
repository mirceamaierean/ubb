package model;

public class PearTree extends Tree{

    public PearTree(int id, int age)
    {
        super(id, age);
    }

    @Override
    public String getTypeOfTree()
    {
        return "Pear Tree";
    }

    @Override
    public String toString()
    {
        return "Pear Tree with id " + this.id + " and age " + this.age;
    }
}
