using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimeTracker : MonoBehaviour
{
    public static float realtimepassed = 0.0f;
    public static float gametimepassed = 0.0f;
    // Use this for initialization
    public float acceleration = 0.1f;
    void Start()
    {
        ScoreScript.scorevalue = 0;
        gametimepassed = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {
        if (!gameOver.gameIsOver)
        {
            Time.timeScale = 1 + (acceleration * Time.deltaTime);
            gametimepassed += Time.deltaTime * Time.timeScale;
            ScoreScript.scorevalue = (int)gametimepassed;
            acceleration += (0.01f);    //there now time gradually increases
        }

        //  Audiospeed.speed = 1 + realtimepassed / 30;
    }
}
