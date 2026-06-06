//새 프로미스 만들어지면 executor 바로 실행됨

const promise = new Promise((resolve,reject)=>{
    console.log("doing something");
    setTimeout(()=>{
        resolve('chanwoong');
        //reject(new Error('no network'))
    },2000)
})

// consumers : then, catch, finally
promise
    .then((value) => {
        console.log(value)
    })
    .catch(err =>{
        console.log(err)
    })
    .finally(() => {
        console.log('finally')
    });

//promise chaining
const fetchNumber = new Promise((resolve,reject) =>{
    setTimeout(() => resolve(1),2000)
});

fetchNumber //1
    .then(num => num * 2) //2
    .then(num => num * 3) //6
    .then(num => {
        return new Promise((resolve,reject) => {
            setTimeout(() => resolve(num-1),1000)
        })
    }) //5
    .then(num => console.log(num)); //5출력
