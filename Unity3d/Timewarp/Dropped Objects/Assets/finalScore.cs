using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class finalScore : MonoBehaviour {
    Text finalText;
   
	// Use this for initialization
	void Start () {
        finalText = GetComponent<Text>();
        finalText.text = " - " + ScoreScript.scorevalue + " - ";
      
	}
	
	// Update is called once per frame
	void Update () {
        //finalText.text = " - " + ScoreScript.scorevalue + " - ";
    }
}
