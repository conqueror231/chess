#include "Game.h"
#include "WindowStateManager.h"
#include "ChessBoard.h"
#include <iostream>
Game::Game()
{
    InnitGUI();
}

Game::Game(sf::VideoMode videoMode_, sf::String windowTitle_)
    : IWindowActivity(videoMode_, windowTitle_)
{
    InnitGUI();
}

void Game::HandleInput()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        static sf::Vector2i chessBoardStartPos(offsetXForChessBoard, offsetYForChessBoard);
        static sf::Vector2i chessBoardEndPos(offsetXForChessBoard + TileSize * 8,
                                                        offsetYForChessBoard + TileSize * 8);
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

        if (isMouseInChessBoard(mousePos, chessBoardStartPos, chessBoardEndPos)) {

            calculateHoveredTilePosition(mousePos, chessBoardStartPos);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            ChessPiece* selectedChessPiece = chessBoard->getChessPieceByPos(selectedTileIndexes.x, selectedTileIndexes.y);
            ChessPiece* clickedChessPiece = chessBoard->getChessPieceByPos(hoveredTileIndexes.x, hoveredTileIndexes.y);

            if (selectedChessPiece && clickedChessPiece) {
                // Attack: selectedChessPiece attacks clickedChessPiece
                selectedChessPiece->Move(hoveredTileIndexes, chessBoard->getChessPieces());
           
               
                std::cout << "Piece at position (" << selectedTileIndexes.x << ", " << selectedTileIndexes.y
                    << ") attacks piece at position (" << hoveredTileIndexes.x << ", " << hoveredTileIndexes.y << ")." << std::endl;

                selectedTileIndexes = sf::Vector2i(-1, -1);
            }
            else if (selectedChessPiece == nullptr && clickedChessPiece == nullptr) {
                selectedTileIndexes = hoveredTileIndexes;
            }
            else if (selectedChessPiece == nullptr) {
                // If no piece is selected, select the new tile
                selectedTileIndexes = hoveredTileIndexes;
         
                std::cout << "Piece selected at tile (" << hoveredTileIndexes.x << ", " << hoveredTileIndexes.y << ")." << std::endl;
            }
            else if (clickedChessPiece == nullptr) {
                // Move: selectedChessPiece moves to hoveredTile
                std::cout << "Piece at position (" << selectedTileIndexes.x << ", " << selectedTileIndexes.y
                    << ") moved to tile (" << hoveredTileIndexes.x << ", " << hoveredTileIndexes.y << ")." << std::endl;

                selectedChessPiece->Move(hoveredTileIndexes, chessBoard->getChessPieces());
                selectedTileIndexes = sf::Vector2i(-1, -1);
               
            }

        }

        }
        else {
            hoveredTileIndexes = sf::Vector2i(-1, -1);
        }      
    }

        if (event.type == sf::Event::Closed)
            window->close();
}


bool Game::isMouseInChessBoard(sf::Vector2i& mousePos, sf::Vector2i& chessBoardStartPos, sf::Vector2i& gamePromptEndPos)
{
    return mousePos.x >= chessBoardStartPos.x && mousePos.x <= gamePromptEndPos.x &&
        mousePos.y >= chessBoardStartPos.y && mousePos.y <= gamePromptEndPos.y;
}

void Game::calculateHoveredTilePosition(sf::Vector2i& mousePos, sf::Vector2i& chessBoardStartPos)
{

    for (int x = 0; x < 8; x++) {
        if (mousePos.x >= chessBoardStartPos.x + TileSize * (x + 1))
            continue;
        for (int y = 0; y < 8; y++) {
            if (mousePos.y >= chessBoardStartPos.y + TileSize * (y + 1))
                continue;

            hoveredTileIndexes.x = x;
            hoveredTileIndexes.y = y;
           // std::cout << "Row: " << y + 1 << ", Column: " << columnsLabels[x] << std::endl;
            break;
        }
        break;
    }
}

void Game::Update()
{

}

void Game::Draw()
{
    window->clear(sf::Color::Cyan);
    
   // chess board
    sf::Color lightColor = sf::Color::White;
    sf::Color darkColor(73, 84, 202);
   
    
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
           
            sf::RectangleShape tile(sf::Vector2f(TileSize, TileSize));
            tile.setPosition(col * TileSize + offsetXForChessBoard, row * TileSize + offsetYForChessBoard);

            if ((row + col) % 2 == 0) {
                tile.setFillColor(lightColor); 
            }
            else {
                tile.setFillColor(darkColor);  
            }

            window->draw(tile);
        }
    }
    // Chess pieces
    
    for (const auto& piece : chessBoard->getChessPieces()) {
        sf::RectangleShape pawnShape(sf::Vector2f(TileSize / 2, TileSize / 2)); 

        if(piece->isWhite)
            pawnShape.setFillColor(sf::Color::Green);
        else
            pawnShape.setFillColor(sf::Color::Black); 


        pawnShape.setPosition(
          
            piece->GetPosition().x * TileSize + offsetXForChessBoard + TileSize / 4,
            piece->GetPosition().y* TileSize + offsetYForChessBoard + TileSize / 4
        );

        window->draw(pawnShape); 
    }
    
    //left side menu 
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(203, 768));
    rectangle.setFillColor(sf::Color(17, 140, 202));  
    window->draw(rectangle);

    //hovering tiles
    if (hoveredTileIndexes.x != -1 && hoveredTileIndexes.y != -1) {
        sf::RectangleShape highlightedTile(sf::Vector2f(TileSize, TileSize));
        highlightedTile.setPosition(hoveredTileIndexes.x * TileSize + offsetXForChessBoard,
        hoveredTileIndexes.y * TileSize + offsetYForChessBoard);
        highlightedTile.setFillColor(sf::Color(135, 215, 255, 128));  
        window->draw(highlightedTile);
    }

    window->display();
}

void Game::Run()
{
    IWindowActivity::Run();
}

void Game::InnitGUI()
{
    chessBoard = &ChessBoard::getInstance();
}
