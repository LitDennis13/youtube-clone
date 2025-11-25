import { useEffect, useState } from "react";

import { PageOptions } from "../../types";
import { SelectedPageStore } from "../../store";

import styles from "./SignInSignUpStyles.module.css";


function LoginPageSignUp() {
    const selectedPage = SelectedPageStore((state) => state.value);
    const [displaySignUpPage, setDisplaySignUpPage] = useState(false);
    const [enteredUserName, setEnteredUserName] = useState(true);
    const [enteredPassword, setEnteredPassword] = useState(true);
    const [passwordsMatch, setPasswordsMatch] = useState(true);

    const [userName, setUserName] = useState("");
    const [password, setPassword] = useState("");
    const [confirmPassword, setConfirmPassword] = useState("");
    
    useEffect(() => {
        selectedPage.setSelectedPage(PageOptions.SignInSignUp);
    }, []);

    function userNameOnInput(event: any) {
        setUserName(event.target.value);
        if (!enteredUserName) {
            setEnteredUserName(true);
        }
    }

    function passwordOnInput(event: any) {
        setPassword(event.target.value);
        if (!enteredPassword) {
            setEnteredPassword(true);
        }
        if (!passwordsMatch) {
            setPasswordsMatch(true);
        }
    }

    function passwordConfirmOnInput(event: any) {
        setConfirmPassword(event.target.value);
        if (!passwordsMatch) {
            setPasswordsMatch(true);
        }
    }

    function signInSignUpOnClick() {
        if (userName === "") {
            setEnteredUserName(false);
        }
        else if (password === "") {
            setEnteredPassword(false);
        }
        else if (displaySignUpPage && password !== confirmPassword) {
            setPasswordsMatch(false);
        }
        else {
            


            setUserName("");
            setPassword("");
            setConfirmPassword("");
        }
    }
    
    function SignInSignUpButtonText() {
        if (!enteredUserName) {
            return "Enter Username";
        }
        else if (!enteredPassword) {
            return "Enter Password";
        }
        else {
            return ("Sign " + (displaySignUpPage ? "Up" : "In"));
        }
    }

    function SwitchPageButtonOnClick() {
        setDisplaySignUpPage(!displaySignUpPage);
        setEnteredUserName(true);
        setEnteredPassword(true);
        setPasswordsMatch(true);
        setConfirmPassword("");
    }

    return (
        <div className={styles.page}>
            <div id={(displaySignUpPage && !passwordsMatch ? styles.signUpExtend : "")} className={styles.main + " " + (displaySignUpPage ? styles.signUp : styles.signIn)}>
                <h1>Sign {displaySignUpPage ? "Up" : "In"}</h1>

                <input type="text" className={styles.inputUserName} value={userName} placeholder="Username" onInput={(event: any) => userNameOnInput(event)} />
                <input id={(displaySignUpPage && !passwordsMatch ? styles.passwordNotMatchInput : "")} type="password" className={styles.inputUserPassword} value={password} placeholder="Password" onInput={(event: any) => passwordOnInput(event)} />
                {displaySignUpPage ? <input id={(!passwordsMatch ? styles.passwordNotMatchInput : "")} type="password" className={styles.inputUserPasswordConfirm} value={confirmPassword} placeholder="Confirm Password" onInput={(event: any) => passwordConfirmOnInput(event)}/> : ""}
                {(displaySignUpPage && !passwordsMatch) ? <p className={styles.passwordNotMatch}>Passwords do not match</p> : ""}
                <button className={styles.signInUpButton } onClick={() => signInSignUpOnClick()}>{SignInSignUpButtonText()}</button>
                <button className={styles.switchPageButton} onClick={() => SwitchPageButtonOnClick()}>Switch to Sign {displaySignUpPage ? "In" : "Up"}</button>
            </div>
        </div>
    );
}

export default LoginPageSignUp;