using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class startGame : MonoBehaviour {

    public AudioSource sound;
    public AudioClip soundClip;

    void Start()
    {
        sound.clip = soundClip;
    }
    void Update ()
    {
        if(Input.GetKeyDown(KeyCode.P))
        {
            SceneManager.LoadScene("Moving Objects");
        }
    }
    public void playGame()
    {
        StartCoroutine(WaitForSound());
        
    }
    IEnumerator WaitForSound() {    //So the sound plays all the way before changing scenes

        //sound.Play();
        sound.PlayOneShot(sound.clip);
        yield return new WaitForSeconds(sound.clip.length);
        SceneManager.LoadScene("Moving Objects");
    }

    
}
