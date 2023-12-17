package exceptions;

public class TreeNotInRepositoryException extends Exception{
    public TreeNotInRepositoryException(String message)
    {
        super(message);
    }
}
