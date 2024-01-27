# Snake Game : 2024-01-27, 4h

```mermaid
classDiagram
    class Game {
        +start()
        +update()
        +render()
    }
    class Snake {
        +update()
        +grow()
        +checkCollision()
    }
    class Food {
        +respawn()
    }
    class GameBoard {
        +draw()
    }
    class InputHandler {
        +handleInput()
    }
    class ScoreBoard {
        +updateScore()
        +draw()
    }

    Game "1" --> "1" Snake : controls
    Game "1" --> "1" Food : contains
    Game "1" --> "1" GameBoard : contains
    Game "1" --> "1" InputHandler : uses
    Game "1" --> "1" ScoreBoard : uses
    Snake "1" --> "0..*" Food : interacts with
    Snake "1" --> "1" GameBoard : moves within
    InputHandler ..> Snake : updates direction
    ScoreBoard ..> Snake : updates score based on snake's actions
```

- `Game`: The main class of the game, it manages the game loop and coordinates interactions between other components.
- `Snake`: This class represents the snake and contains the logic for movement, growth, and collision detection.
- `Food`: A class representing the snake's food, responsible for appearing in random locations on the game field.
- `GameBoard`: A class responsible for rendering the game field.
- `InputHandler`: A class for handling user input and managing the direction of the snake's movement.
- `ScoreBoard`: A class for displaying and updating the game's score.
