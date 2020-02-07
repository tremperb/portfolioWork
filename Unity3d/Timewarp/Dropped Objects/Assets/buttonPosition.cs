using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class buttonPosition : MonoBehaviour {
    public Vector2 screenBounds;
    Button playButton;
    float size;
    // Use this for initialization
    void Start () {
        screenBounds = new Vector2(Camera.main.aspect * Camera.main.orthographicSize, Camera.main.orthographicSize); //get our camera bounds
        playButton = GetComponent<Button>();
        Vector2 pos = screenBounds;
        pos.x = screenBounds.x / 10;
        pos.y = screenBounds.y / 10;
        playButton.transform.localScale = pos;
    }
	
	// Update is called once per frame
	void Update () {
		
	}
    
}
