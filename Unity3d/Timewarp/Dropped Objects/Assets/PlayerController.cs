using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {
    public float moveSpeed = 3f;
    Rigidbody2D body;
    Vector2 playerMovement;
    ////////////
    int walk = 0;
    public Sprite[] Sprite_Pic;
    public float wait = 0f;
    public float armSpeed = 0.5f;
    ////////////
    public Vector2 screenBounds;
    float playerHeight;
    ////
    public ParticleSystem particleOne;
    public ParticleSystem particleUp;

    void Start () {
        body = GetComponent<Rigidbody2D>(); //get our body to move
        playerHeight = transform.localScale.y / -2; //get our objects height so it is not centered on bounds
        screenBounds = new Vector2(Camera.main.aspect * Camera.main.orthographicSize, Camera.main.orthographicSize + playerHeight); //get our camera bounds


    }

    // Update is called once per frame
    void Update () {
        
        if (wait > armSpeed)
        {
            getSprite();    //update character
            wait = 0;
        }
        wait += Time.deltaTime;

        getMovement();
        getBounds();
	}

   
    void getBounds()
    {
        if (transform.position.y <= -screenBounds.y / 2)
        {
            transform.position = new Vector2(transform.position.x, -screenBounds.y / 2);    //Checks if it goes out of bounds and then changes the position 
        }                                                                                   // keeping it in bounds
        else if (transform.position.y >= screenBounds.y / 2)
        {
            transform.position = new Vector2(transform.position.x, screenBounds.y / 2);
        }
    }

    void getMovement()
    {

        float getY = Input.GetAxis("Vertical"); //gets our input to move up, don't need x axis

        Vector3 movement = new Vector3(0, getY, 0) * moveSpeed * Time.deltaTime;

        body.MovePosition(transform.position + movement);
        if (Input.GetKey("up") || Input.GetKey("w")) {

            particleUp.Play();  //play this to make it go faster and further when going up
            particleOne.Stop();
        }
        else if (Input.GetKey("down") || Input.GetKey("s"))
        {
            particleUp.Stop();  //going down so stop both
            particleOne.Stop();
        }
        else
        {
            particleOne.Play(); //otherwise do default
            particleUp.Stop();
        }
    }

    void getSprite()
    {
        GetComponent<SpriteRenderer>().sprite = Sprite_Pic[walk]; //get our sprite 
        walk++; //get next movement
        if (walk >= 2)  //if it got that reinitialize to 0 because theres only 2 movement
            walk = 0;
    }

}
