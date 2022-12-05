using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CageTrapFall : MonoBehaviour
{

    public Rigidbody g;
    public Collider cageCollision;
    public Collider cageTrigger;
    GameObject player;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.FindWithTag("Player");
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
        if (other.tag == "Player")
        {
            LifeController lc = other.GetComponent<LifeController>();
            lc.TakeDamage(1);
            //Destroy(gameObject);
        }
    }

    IEnumerator ITimeGeneration()
    {
        yield return new WaitForSeconds(5.0f);
        transform.position = new Vector3(0,0,0);
        StopCoroutine(ITimeGeneration());
    }
}
