/*
TODO: 
Build a playground: four walls (four boxs)
Make a player 
Move the player around
collision between player and ball
change the walls with vectors as in applyforce example, also may try edges b2edgeshape
Make my own test
create all the bodies in loop 
*/

#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Window.hpp>

//Creating a world (global)
b2Vec2 gravity(0.0f, 0.0f);     //no gravity in x or y
b2World world(gravity);

void create_players(){
    //Create dynamic body (ball)
    b2BodyDef player1;
    b2BodyDef player2;
    b2BodyDef player3;
    b2BodyDef player4;
    b2BodyDef players[] = {player1, player2, player3, player4};
    
    for(int i=0; i<4; i++){
        players[i].type = b2_dynamicBody;
    }

    player1.position.Set(1.5f, 0.5f);
    player2.position.Set(1.5f, 1.0f);
    player3.position.Set(-1.5f, 0.5f);
    player4.position.Set(-1.5f, 1.0f);

    b2Body* p1 = world.CreateBody(&player1);
    b2Body* p2 = world.CreateBody(&player2);
    b2Body* p3 = world.CreateBody(&player3);
    b2Body* p4 = world.CreateBody(&player4);
}

int main() {

    //Creating a world
    //b2Vec2 gravity(0.0f, 0.0f);     //no gravity in x or y
    //b2World world(gravity);

    //Creating walls
    b2BodyDef body1;    
    b2BodyDef body2;    
    b2BodyDef body3;    
    b2BodyDef body4;    
    body1.position.Set(0.0f, 0.0f); //playground
    body2.position.Set(1.50f, 0.75f); //playground 
    body3.position.Set(0.0f, 1.5f); //playground 
    body4.position.Set(-1.5f, 0.75f); //playground  

    b2Body* wall1 = world.CreateBody(&body1);  //create the body
    b2Body* wall2 = world.CreateBody(&body2);  //create the body
    b2Body* wall3 = world.CreateBody(&body3);  //create the body
    b2Body* wall4 = world.CreateBody(&body4);  //create the body

    b2PolygonShape groundBox1;   //create the shape
    groundBox1.SetAsBox(3.6f, 0.3f);   //

    b2PolygonShape groundBox2;   //create the shape
    groundBox2.SetAsBox(0.3f, 1.5f);   //

    wall1->CreateFixture(&groundBox1, 0.0f);
    wall2->CreateFixture(&groundBox2, 0.0f);
    wall3->CreateFixture(&groundBox1, 0.0f);
    wall4->CreateFixture(&groundBox2, 0.0f);

    //Create dynamic body (ball)
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.75f);
    //bodyDef.allowSleep = false;
    b2Body* body = world.CreateBody(&bodyDef);
    //shape
    b2CircleShape player;
    player.m_p.Set(0.0f, 0.0f);
    player.m_radius = 0.1f;

    //fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &player;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 1;

    body->CreateFixture(&fixtureDef);
    b2Vec2 p = body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
    b2Vec2 f (0.0f, 2.0f);
    body->ApplyForce(f, p, true);

    //simulation
    //Let's start simulation
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int32 i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        b2Vec2 position = body->GetPosition();
        float angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }

    //clean the world
    //world->DestroyBody(body);
    return 0;
}
