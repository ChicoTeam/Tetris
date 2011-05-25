
#include <iostream>
#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "piece.hpp"

int main()
{

  //Create the board
  Tetris::Board board(10,20);


  //Create the rendering window
  sf::RenderWindow window(sf::VideoMode(600,800, 32), "Tetris");
  sf::View view(sf::FloatRect(0,0,15,20));
  window.SetView(view);


  //Setup the clock and time variables
  sf::Clock clock;
  double totalTime = 0;
  double deltaTime = 0;
  double nextStepTime = 0.5;
  float gameSpeed = 5;
  bool stepSuccessful = true;


  //Setup the paused boolean and pause text
  bool paused = false;
  sf::String pausedText("Paused (P)");
  pausedText.SetSize(1);
  pausedText.SetColor(sf::Color::Black);

  //board.Randomise();
  Tetris::Piece* piece = new Tetris::Piece(&board, 1,1);
  

  //Main loop
  while(window.IsOpened())
  {

    //Continue time if the game isn't paused
    if(!paused)
    {
      deltaTime = clock.GetElapsedTime();
      totalTime += deltaTime;
    }
    clock.Reset();


    //Get input

    int movePiece = 0;

    sf::Event event;
    while(window.GetEvent(event))
    {
      if(event.Type == sf::Event::Closed)
	window.Close();
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
	  stepSuccessful = false;
	}

	if(event.Key.Code == sf::Key::P)
	  paused = !paused;

	if(event.Key.Code == sf::Key::Escape)
	  window.Close();
      }
    }

    //Move pieces, check rows, etc. (only if game isn't paused)
    if(!paused)
    {

      if(movePiece != 0)
	piece->Move(movePiece,0);

      if( totalTime >= nextStepTime)
      {
	nextStepTime = totalTime + (1 / gameSpeed);
	stepSuccessful = piece->Move(0,1); //move the piece down 1 if we can
      }

      if(!stepSuccessful)
      {
	//Can't move the piece down, lets place it and get a new one
	piece->Place();
	delete piece;
	piece = new Tetris::Piece(&board,1,1);
	stepSuccessful = true;
      }

      //Check rows
      board.CheckRows();

    }

    //Render the game
    window.Clear();    
    board.Render(window);
    piece->Render(window);
    
    if(paused)
      window.Draw(pausedText);

    window.Display();
  }
  return 0;
}
