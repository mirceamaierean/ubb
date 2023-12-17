package controller;

import repository.IRepository;
import repository.Repository;

import model.Tree;
public class Controller {

    IRepository repository;

    public Controller(IRepository repository)
    {
        this.repository = repository;
    }

    public void addTree(model.Tree tree) throws exceptions.FullRepositoryException
    {
        repository.addTree(tree);
    }

    public void removeTree(int id) throws exceptions.TreeNotInRepositoryException
    {
        repository.removeTree(id);
    }

    public Tree[] getTrees()
    {
        return repository.getTrees();
    }

    public Tree[] getAllTreesWithAgeOlderThanValue(int age)
    {
        Tree[] result = new Tree[this.repository.getSize()];
        int size = 0;
        for (Tree tree : this.repository.getTrees()) {
//            if (tree == null)
//                break;
//        }
            if (tree.getAge() > age) {
                result[size++] = tree;
            }
        }
        return result;
    }
}
