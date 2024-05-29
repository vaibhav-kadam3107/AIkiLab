import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class DepthLimitedSearch {

    static int[][] grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };

    static Point initialPosition = new Point(0, 0);
    static Point goalPosition = new Point(4, 4);

    static class Problem {
        int[][] grid;
        Point initialState;
        Point goalState;

        Problem(int[][] grid, Point initial, Point goal) {
            this.grid = grid;
            this.initialState = initial;
            this.goalState = goal;
        }

        boolean isGoal(Point state) {
            return state.equals(goalState);
        }

        List<Point> expand(Point state) {
            List<Point> movements = Arrays.asList(
                new Point(0, -1), new Point(0, 1),
                new Point(-1, 0), new Point(1, 0)
            );
            List<Point> validMoves = new ArrayList<>();
            for (Point move : movements) {
                int newX = state.x + move.x;
                int newY = state.y + move.y;
                if (newX >= 0 && newX < grid.length && newY >= 0 && newY < grid[0].length && grid[newX][newY] == 0) {
                    validMoves.add(new Point(newX, newY));
                }
            }
            return validMoves;
        }
    }

    static List<Point> depthLimitedSearch(Problem problem, int depthLimit) {
        return recursiveDLS(problem.initialState, problem, depthLimit);
    }

    static List<Point> recursiveDLS(Point node, Problem problem, int depthLimit) {
        if (problem.isGoal(node)) {
            List<Point> path = new ArrayList<>();
            path.add(node);
            return path;
        } else if (depthLimit == 0) {
            return null;
        } else {
            for (Point child : problem.expand(node)) {
                List<Point> result = recursiveDLS(child, problem, depthLimit - 1);
                if (result != null) {
                    result.add(0, node);
                    return result;
                }
            }
            return null;
        }
    }

    public static void main(String[] args) {
        Problem problem = new Problem(grid, initialPosition, goalPosition);
        int depthLimit = 10;
        List<Point> path = depthLimitedSearch(problem, depthLimit);

        if (path == null) {
            System.out.println("No path found within the depth limit.");
        } else {
            System.out.println("Path found: " + path);
            visualizePath(grid, path);
        }
    }

    static void visualizePath(int[][] grid, List<Point> path) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Grid with DLS Path");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.add(new GridPanel(grid, path, initialPosition, goalPosition));
            frame.setSize(600, 600);
            frame.setVisible(true);
        });
    }

    static class GridPanel extends JPanel {
        int[][] grid;
        List<Point> path;
        Point initialPosition;
        Point goalPosition;

        GridPanel(int[][] grid, List<Point> path, Point initialPosition, Point goalPosition) {
            this.grid = grid;
            this.path = path;
            this.initialPosition = initialPosition;
            this.goalPosition = goalPosition;
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            int cellSize = Math.min(getWidth() / grid[0].length, getHeight() / grid.length);
            for (int i = 0; i < grid.length; i++) {
                for (int j = 0; j < grid[i].length; j++) {
                    if (grid[i][j] == 1) {
                        g.setColor(Color.BLACK);
                    } else {
                        g.setColor(Color.WHITE);
                    }
                    g.fillRect(j * cellSize, i * cellSize, cellSize, cellSize);
                    g.setColor(Color.GRAY);
                    g.drawRect(j * cellSize, i * cellSize, cellSize, cellSize);
                }
            }

            if (path != null) {
                g.setColor(Color.BLUE);
                for (Point p : path) {
                    g.fillOval(p.y * cellSize + cellSize / 4, p.x * cellSize + cellSize / 4, cellSize / 2, cellSize / 2);
                }
            }

            g.setColor(Color.GREEN);
            g.fillOval(initialPosition.y * cellSize + cellSize / 4, initialPosition.x * cellSize + cellSize / 4, cellSize / 2, cellSize / 2);

            g.setColor(Color.RED);
            g.fillOval(goalPosition.y * cellSize + cellSize / 4, goalPosition.x * cellSize + cellSize / 4, cellSize / 2, cellSize / 2);
        }
    }
}
