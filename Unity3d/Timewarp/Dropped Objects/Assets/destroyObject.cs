using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class destroyObject : MonoBehaviour {
    Renderer m_Renderer;
    bool hasAppeared = false;
    // Use this for initialization
    void Start () {
        m_Renderer = GetComponent<Renderer>();
    }
	
	// Update is called once per frame
	void Update () {
        if (m_Renderer.isVisible)
        {
            hasAppeared = true;
        }
        if(hasAppeared)
        {
            if(!m_Renderer.isVisible)
            {
                Destroy(gameObject);
            }
        }
    }
}
