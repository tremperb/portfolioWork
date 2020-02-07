using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement; //so we can use scene manager
public class gameOver : MonoBehaviour {

    // Use this for initialization
    public static bool gameIsOver = false;
    public GameObject gameOverUI;
    /// <summary>
    public AudioSource sound;
    public AudioClip soundClip;
    /// <summary>
    public AudioSource deathSound;
    public AudioClip deathClip;
    private bool soundPlayed = false;
    /// </summary>
    void Start () {
        sound.clip = soundClip;
        deathSound.clip = deathClip;
        
	}
	
	// Update is called once per frame
	void Update () {
        if(gameIsOver)
        {
            if(!soundPlayed)
            {
                deathSound.PlayOneShot(deathSound.clip);
                soundPlayed = true;
            }
            
            Pause();
        }
       
	}

    void Pause ()
    {
        
        gameOverUI.SetActive(true);
        Time.timeScale = 0f;
        gameIsOver = true;
    }

    public void Restart()
    {
        sound.PlayOneShot(sound.clip);  //Same here
        StartCoroutine(WaitForSoundRestart()); //Call restart function
        
    }

    public void getMainScreen ()
    {
        sound.PlayOneShot(sound.clip);  //play the sound
        StartCoroutine(WaitForSoundMain()); //call function to get main
        
    }


    IEnumerator WaitForSoundMain()
    {    //So the sound plays all the way before changing scenes

        
        //sound.PlayOneShot(sound.clip);  //play the sound
        yield return new WaitForSecondsRealtime(sound.clip.length); //wait to do anything until sound finishes need real time since time scale is 0
        //Time.timeScale = 1f;    //reset timescale
        SceneManager.LoadScene("Moving Objects");   //reset objects scene
        SceneManager.LoadScene("mainMenu"); //switch to main menu
        gameIsOver = false;
        Time.timeScale = 1f;
    }

    IEnumerator WaitForSoundRestart()
    {    //So the sound plays all the way before changing scenes
        Debug.Log("Waiting");
        //sound.PlayOneShot(sound.clip);  //Same here
        yield return new WaitForSecondsRealtime(sound.clip.length);
        SceneManager.LoadScene("Moving Objects"); // relod scene and start again
        gameIsOver = false; //Now game is not over so set to false
    }

    
}
