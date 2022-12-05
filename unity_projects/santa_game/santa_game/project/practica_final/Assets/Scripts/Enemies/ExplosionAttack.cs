using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExplosionAttack : MonoBehaviour
{
    EnemySimpleMovement mov;
    Follow foll;
    bool exploted = false;
    [SerializeField]
    private GameObject explosionRadius;
    GameObject renderer;

    // Start is called before the first frame update
    void Start()
    {
        mov = GetComponent<EnemySimpleMovement>();
        foll = GetComponent<Follow>();
        renderer = gameObject.transform.Find("Object001").gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        if (!exploted)
        {
            if (foll.distance < 2 && !mov.animator.GetBool("attack"))
            {
                mov.on_movement = false;
                //mov.animator.SetTrigger("attack");
                mov.animator.SetBool("walk", false);
                exploted = true;
                StartCoroutine(Explosion());
            }
        }
        else {
            if (!mov.animator.GetBool("attack")) {


            }
        }
    }
    private void OnEnable()
    {
        exploted = false;
        explosionRadius.SetActive(false);
        //renderer.SetActive(true);

        //mov.animator.SetBool("walk", true);
       // if (mov.animator.GetBool("attack"))mov.animator.ResetTrigger("attack");
    }
    IEnumerator Explosion()
    {
        mov.attacking = true;
        mov.animator.SetTrigger("attack");
        yield return new WaitForSeconds(1.9f);
        explosionRadius.SetActive(true);
        yield return new WaitForSeconds(0.1f);
        gameObject.SetActive(false);
        explosionRadius.SetActive(false);
        renderer.SetActive(true);
        mov.on_movement = true;
        mov.attacking = false;
    }
}
