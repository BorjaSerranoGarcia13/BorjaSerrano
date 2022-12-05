using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Follow : MonoBehaviour
{
    [SerializeField]
    string tag_to_find="Player";
    
    [SerializeField]
    float rotationSpeed=50;
    GameObject[] to_follow;
    [SerializeField]
    float max_distance=0;
    public float distance;
    EnemySimpleMovement mov;
    // Start is called before the first frame update
    void Start()
    { 
        to_follow = GameObject.FindGameObjectsWithTag(tag_to_find);
        distance = Vector3.Distance(transform.position, to_follow[0].transform.position);
        mov = GetComponent<EnemySimpleMovement>();
    }

    // Update is called once per frame
    void Update()
    {
        distance= Vector3.Distance(transform.position,to_follow[0].transform.position);
        if (distance < max_distance)
        {
            if (!mov) mov.follow = true;
            this.gameObject.transform.rotation = Quaternion.Slerp(this.gameObject.transform.rotation,
                Quaternion.LookRotation(to_follow[0].transform.position - this.gameObject.transform.position), rotationSpeed * Time.deltaTime);
        }
        else { if (!mov) mov.follow = false; }
        
    }
}
