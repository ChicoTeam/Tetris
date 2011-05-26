#include "tetris.hpp"
#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "piece.hpp"

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
    int score = 0;
    bool freshPiece = true;

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
	if(board.CheckRows())
	  gameSpeed += 0.5;
      }

      //Render the game
      window.Clear();    
      board.Render(window);
      piece->Render(window);
    
      if(paused)
	window.Draw(pausedText);

      window.Display();

    }

    //Game over
    sf::String gameOverText("GAME OVER");
    gameOverText.SetSize(2);
    gameOverText.SetColor(sf::Color::White);

    sf::Clock gameOverClock;
    while(gameOverClock.GetElapsedTime() < 5)
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
	  if(event.Key.Code == sf::Key::Escape)
	    return score;
	}
      }
      
      window.Clear();
      window.Draw(gameOverText);
      window.Display();

    }
    
    return score;
  }
}
