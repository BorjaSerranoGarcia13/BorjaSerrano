using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CageTrapFall : MonoBehaviour
{
    public Rigidbody g;
    public Collider cageCollision;
    public Collider cageTrigger;
    CharacterController player;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player").GetComponent<CharacterController>();
    }

   // Update is called once per frame
    void Update()
    {
        if (g.useGravity)
        {
            cageCollision.isTrigger = false;
            StartCoroutine(ITimeGeneration());
        }  
    }

    void OnTriggerEnter(Collider other)
    {
        if (other == player)
        {
            Destroy(gameObject);
        }
    }

    IEnumerator ITimeGeneration()
    {  
        yield return new WaitForSeconds(5.0f);
        Destroy(gameObject);
        StopCoroutine(ITimeGeneration());
    }
}
