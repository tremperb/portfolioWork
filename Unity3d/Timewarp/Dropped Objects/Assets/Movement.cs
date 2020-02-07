using UnityEngine;

public class Movement : MonoBehaviour {
    
    public float moveSpeed = 5f;
    public float rotateSpeed = 20f;
    public Vector3 degrees;
   
    // Use this for initialization
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
        transform.Translate(-moveSpeed * Time.deltaTime, 0, 0);

        //transform.RotateAround(transform.position, transform.position, 20 * Time.deltaTime); //kinda cool makes the weird rotate effect
    }    

}
