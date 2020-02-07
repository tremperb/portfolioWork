using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class hazardSpawner : MonoBehaviour {
    public GameObject hazard;
    float randY;
    Vector2 whereToSpawn;
    public float spawnRate = 2f;
    float nextSpawn = 0.0f;

    public Vector2 screenBounds;
    float ourRange;
    void Start () {
        screenBounds = new Vector2(Camera.main.aspect * Camera.main.orthographicSize, Camera.main.orthographicSize);

    }
	
	// Update is called once per frame
	void Update () {
		if(Time.time > nextSpawn)
        {
            ourRange = screenBounds.y / 2;
            nextSpawn = Time.time + spawnRate;
            randY = Random.Range(-ourRange, ourRange);  //get random range within camera bounds
            whereToSpawn = new Vector2(transform.position.x, randY);
            Instantiate(hazard, whereToSpawn, Quaternion.identity);
        } 
        
    }

}
