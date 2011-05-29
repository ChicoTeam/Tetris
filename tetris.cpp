#include "tetris.hpp"
#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "piece.hpp"
#include <sstream>

namespace Tetris
{
  int Tetris(sf::RenderWindow &window)
  {
    //Create the board
    Tetris::Board board(10,20);

    sf::View view(sf::FloatRect(0,0,15,20));
    window.SetView(view);


    //Setup the clock and time variables
    sf::Clock clock;
    double totalTime = 0;
    double deltaTime = 0;
    double nextStepTime = 0;
    float gameSpeed = 1;

    //Setup the paused boolean and pause text
    bool paused = false;
    sf::String pausedText("Paused (P)");
    pausedText.SetSize(1);
    pausedText.SetColor(sf::Color::Black);

    //board.Randomise();
    Tetris::Piece* piece = new Tetris::Piece(&board, 1,1);
  
    bool gameOver = false;

    bool freshPiece = true;

    //Score stuff
    int score = 0;
    sf::String scoreTextLabel("Score");
    scoreTextLabel.SetSize(1);
    scoreTextLabel.SetColor(sf::Color::White);
    scoreTextLabel.SetPosition( 11, 2);
    sf::String scoreText;
    scoreText.SetSize(1);
    scoreText.SetColor(sf::Color::White);
    scoreText.SetPosition( 11, 3.5);
    while(!gameOver)
    {
      //Continue time if the game isn't paused
      if(!paused)
      {
	deltaTime = clock.GetElapsedTime();
	totalTime += deltaTime;
	nextStepTime -= deltaTime;
      }
      clock.Reset();


      //Get input

      int movePiece = 0;

      sf::Event event;
      while(window.GetEvent(event))
      {
	if(event.Type == sf::Event::Closed)
	{
	  window.Close();
	  return score;
	}
	
	if(event.Type == sf::Event::KeyPressed)
	{
	  if(event.Key.Code == sf::Key::Left)
	    movePiece -= 1;

	  if(event.Key.Code == sf::Key::Right)
	    movePiece += 1;

	  if(event.Key.Code == sf::Key::Up)
	    piece->Rotate();

	  if(event.Key.Code == sf::Key::Down)
	  {
	    //Drop the piece immediately
	    bool moving = true;
	    while(moving)
	      moving = piece->Move(0,1);
	    freshPiece = false;
	  }

	  if(event.Key.Code == sf::Key::P)
	    paused = !paused;

	  if(event.Key.Code == sf::Key::Escape)
	  {
	    window.Close();
	    return score;
	  }
	}
      }

      //Move pieces, check rows, etc. (only if game isn't paused)
      if(!paused)
      {

	if(movePiece != 0)
	  piece->Move(movePiece,0);

	if( nextStepTime < 0 )
	{
	  nextStepTime = (1 / gameSpeed);

	  if( piece->Move(0,1) ) //If we moved the piece down one block successfully
	  {
	    freshPiece = false; //It's moved without hitting anything, it's no longer fresh.
	  }
	  else
	  {
	    if(freshPiece) //If the fresh piece couldn't move down we must be full: game over
	    {
	      gameOver = true;
	      continue; //Skip the rest of this cycle
	    }
	    else //Wasn't a fresh piece, but it will be now
	    {
	      //Can't move down anymore, time to be placed and get a new piece
	      piece->Place();
	      delete piece;
	      piece = new Tetris::Piece(&board,1,1);
	      freshPiece = true;
	    }
	  }
	}

	//Check rows
	int rowsCleared = board.CheckRows();
	if(rowsCleared > 0)
	{
	  score += (100 * (rowsCleared * rowsCleared) * gameSpeed);
	  // Simple scoring mechanic
	  //exponential score increase based on the number of rows cleared

	  gameSpeed += ( 0.1 * rowsCleared ); //Increase the game speed a little.
	}
      }

      //Render the game
      window.Clear();    
      board.Render(window);
      piece->Render(window);

      window.Draw(scoreTextLabel);

      /*
	I do not like this way of converting the score to a string.
	It's messy, nonportable and can overflow a buffer with a large enough score.
	I'll figure out a better way later.
      */
	  std::stringstream ss;
	  ss << score;
	  char scoreString[16];
	  ss >> scoreString;
      scoreText.SetText(scoreString);
      window.Draw(scoreText);
    
      if(paused)
	window.Draw(pausedText);

      window.Display();

    }

    //Game over
    sf::String gameOverText("GAME OVER");
    gameOverText.SetSize(1.5);
    gameOverText.SetColor(sf::Color::White);
    gameOverText.SetPosition(2,6);


    //Ewww, int conversion again.
    std::stringstream ss;
    ss << score;
    char scoreString[16];
    ss >> scoreString;
    scoreText.SetText(scoreString);
    scoreText.SetPosition(5,10);


    while(true)
    {
      //Keep pumping the events, we don't want the window to freeze
      sf::Event event;
      while(window.GetEvent(event))
      {
	if(event.Type == sf::Event::Closed)
	{
	  window.Close();
	  return score;
	}
	
	if(event.Type == sf::Event::KeyPressed)
	{
	  //Esc still closes the game
	  if(event.Key.Code == sf::Key::Escape)
	    window.Close();

	  //Press any key to close the score screen
	  return score;
	}
      }
      
      window.Clear();
      window.Draw(gameOverText);
      window.Draw(scoreText);
      window.Display();

    }
    
    return score;
  }
}
