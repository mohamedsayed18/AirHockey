/*
TODO: 
Build a playground: a static box
Make a player 
Move the player around
collision between player and ball
*/

#include <iostream>
#include <box2d/box2d.h>

int main() {

    //Creating a world
    b2Vec2 gravity(0.0f, 0.0f);     //no gravity in x or y
    b2World world(gravity);

    //creating ground body
    b2BodyDef groundBodyDef;    //body definition
    groundBodyDef.position.Set(0.0f, 0.0f); //playground 

    b2Body* groundBody = world.CreateBody(&groundBodyDef);  //create the body

    b2PolygonShape groundBox;   //create the shape
    groundBox.SetAsBox(50.0f, 10.0f);   //100 meter wide, 20 meter tall
    groundBody->CreateFixture(&groundBox, 0.0f);

    //create dynamic body (player)
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 8.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    //shape
    b2CircleShape player;
    player.m_p.Set(2.0f, 3.0f);
    player.m_radius = 0.5f;

    //fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &player;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    body->SetLinearVelocity(b2Vec2(0,2));

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