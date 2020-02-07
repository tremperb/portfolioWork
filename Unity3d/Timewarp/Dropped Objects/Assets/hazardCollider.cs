using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class hazardCollider : MonoBehaviour {
    
    
	void OnTriggerEnter2D (Collider2D other) //if the object hit the player
    {
        //Don't need to check if it was player because that is the only possibility
        //Time.timeScale = 0;

        //gameOver.SetActive(true);
        gameOver.gameIsOver = true;
        
    }

    
}
