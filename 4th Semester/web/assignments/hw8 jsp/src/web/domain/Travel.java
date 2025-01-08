package web.domain;

import java.time.LocalDateTime;

public class Travel {
    private int id;
    private int userId;
    private LocalDateTime startTime;

    private boolean isFinished;

    // Constructors
    public Travel(int id, int userId, LocalDateTime startTime) {
        this.id = id;
        this.userId = userId;
        this.startTime = startTime;
        this.isFinished = false;
    }

    public Travel(int userId, LocalDateTime startTime) {
        this.userId = userId;
        this.startTime = startTime;
        this.isFinished = false;
    }

    // Getters and setters
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getUserId() {
        return userId;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }

    public LocalDateTime getStartTime() {
        return startTime;
    }

    public void setStartTime(LocalDateTime startTime) {
        this.startTime = startTime;
    }

    public boolean isFinished() {
        return isFinished;
    }

    public void setFinished(boolean isFinished) {
        this.isFinished = isFinished;
    }

    // Override toString for easy debugging
    @Override
    public String toString() {
        return "Travel{" +
                "id=" + id +
                ", userId=" + userId +
                ", startTime=" + startTime +
                '}';
    }
}
