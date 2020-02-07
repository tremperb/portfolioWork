using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class randomSpawner : MonoBehaviour {
    private int rand;
    public Sprite[] Sprite_Pic;
    Vector2 temp;
    private float randSize;
    /// <summary>
    /// ////
    /// </summary>
    Vector2 screenBounds;
    public float minObjSize = 2f;
    public float maxObjSize = 5f;
    // Use this for initialization
    void Start () {
        screenBounds = new Vector2(Camera.main.aspect * Camera.main.orthographicSize, Camera.main.orthographicSize);
        getRandSize();

        rand = Random.Range(0, Sprite_Pic.Length);
        GetComponent<SpriteRenderer>().sprite = Sprite_Pic[rand];
	}
	
	// Update is called once per frame
	void Update () {
        
	}

    void getRandSize ()
    {
        minObjSize = screenBounds.y / 4;
        maxObjSize = screenBounds.y / 1.5f;
        randSize = Random.Range(minObjSize, maxObjSize);
        temp = transform.localScale;
        temp.x = randSize;
        temp.y = randSize;
        transform.localScale = temp;
    }
}
