using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckGround : MonoBehaviour
{
    float distToGround;
    Collider col;
    // Start is called before the first frame update
    void Start()
    {
        col=GetComponent<Collider>();
        distToGround = col.bounds.size.y;


    }
    public bool IsOnGround() {

        if (Physics.Raycast(col.bounds.center, Vector3.down, distToGround))
        {
            return true;
        }

        else {
            return false;
        }
    }
    
}
