import OtherJavaCode.TestClass;

class Main{
    public static void main(String args[]) {
        TestClass testObject = new TestClass(3);
        System.out.println("After initialization: " + testObject.getValue());

        mutateTestObject(testObject, 4);
        System.out.println("After mutateTestObject: " + testObject.getValue());

        reassignTestObject(testObject, 5);
        System.out.println("After reassignTestObject: " + testObject.getValue());

        testObject = new TestClass(6);
        System.out.println("After reassignment: " + testObject.getValue());

        // Conclusion: Java object variables are like C++ pointer variables (and maybe also 
        //  references), not C++ object variables
    }

    private static void mutateTestObject(TestClass testObject, int newValue) {
        testObject.setValue(newValue);
    }

    private static void reassignTestObject(TestClass testObject, int newTestClassValue) {
        testObject = new TestClass(newTestClassValue);
    }
}