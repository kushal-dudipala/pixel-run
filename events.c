#include "main.h"
#include "events.h"

/* 
//    Check for collision between the player and an enemy.
//    Returns 1 if there is a collision, otherwise returns 0.
*/
int checkCollision(Player player, Enemies enemy) {
    return (player.row + player.width > enemy.row) && 
            (player.row < enemy.row + enemy.width) && 
            (player.col < enemy.col + enemy.height) && 
            (player.col + player.height > enemy.col);
}

/* 
//    Check for collision between the player and the goal.
//    Returns 1 if there is a collision, otherwise returns 0.
*/
int checkGoalCollision(Player player, Goal goal) {
    return (player.row + player.width > goal.row) && 
            (player.row < goal.row + goal.width) && 
            (player.col < goal.col + goal.height) && 
            (player.col + player.height > goal.col);
}